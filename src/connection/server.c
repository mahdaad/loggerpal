#include "server.h"
#include "utils/colors.h"
#include "config/bootstrap.h"
#include "queue/zmqPublish.h"
#include "plugin/pluginRegistry.h"
#include "queue/zmqReply.h"
#include "plugin/pluginWatcher.h"
#include "http/httpServer.h"
#include "headCache/headCache.h"
#include "utils/debug.h"
#include <time.h>

#define MAX_ATOM_THREAD 32
// 8KB max frame size
#define MAX_ATOM_SIZE 8192

Atom_t **__buffer;
size_t __buffer_pointer;

SOCKFD connectionServerCreate(int port) {

    __buffer = malloc(sizeof(Atom_t *) * CFG_ATOM_BUFFER);
    __buffer_pointer = 0;

    // Welcome message!
    char *splash_text = ""
                        "\n"
                        " _     _  __  _     _     ____  ____ \n"
                        "| |__ | ||  \\| |   | |__ / () \\/ (_,`\n"
                        "|____||_||_|\\__|   |____|\\____/\\____)\n"
                        "\n";
    fprintf(stdout, "%s", splash_text);
    if (CFG_DEBUG) {
        fprintf(stdout, "\033[0;33mWARNING:\033[0m %s!!DEBUG MODE!!%s\n", FG_RED, FG_RESET);
    }
    // Creating the socket FD (UDP)
    SOCKFD fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        fprintf(stderr, "Cannot create the socket file descriptor\n");
        exit(EXIT_FAILURE);
    }
    // Setting socket options
    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        fprintf(stderr, "Cannot set socket options\n");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    // Bind SockFD to port
    if (bind(fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        fprintf(stderr, "Cannot bind socket FD to port\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Max Atom threads %s%d%s\n", FG_CYAN, MAX_ATOM_THREAD, FG_RESET);
    fprintf(stdout, "Server has been bind to port %s%d%s\n", FG_CYAN, port, FG_RESET);

    pluginPrepareRegistry();
    fprintf(stdout, "Plugin registry is prepared, Max plugin capacity %s%d%s\n", FG_CYAN, MAX_PLUGIN_NUMBER, FG_RESET);
    return fd;
}

void flush_buffer() {
    clock_t start_time, end_time;
    double elapsed_time;
    if (CFG_DEBUG) {
        fprintf(stdout, "%s-- Flushing buffer --%s\n", FG_CYAN, FG_RESET);
        start_time = clock();
    }
    for (size_t i = 0; i < CFG_ATOM_BUFFER; i++) {
        Atom_t *atom = __buffer[i];
        unsigned char *output;
        size_t length = atomSerialize(&output, atom);
        queueZmqSendBytes("ATOM", output, length);
        atomFree(atom);
        free(output);
    }
    __buffer_pointer = 0;
    if (CFG_DEBUG) {
        end_time = clock();
        elapsed_time = (double) (end_time - start_time) / CLOCKS_PER_SEC * 1000;
        fprintf(stdout, "%s-- Buffer flushed (%fms) --%s\n", FG_CYAN, elapsed_time, FG_RESET);
    }
}

void *handle_atom(void *buffer) {

    Atom_t *atom = atomFromBuffer(buffer);

    __buffer[__buffer_pointer++] = atom;
    if (__buffer_pointer == CFG_ATOM_BUFFER) {
        flush_buffer();
    }

    Atom_t *data = (Atom_t *) atom;
    if (CFG_DEBUG) {
        atomPrint(data);
    }
    appendAtomCache(*data);
    free(buffer);
    return 0;
}

_Noreturn void *readFromSocket(void *serverfd) {
    SOCKFD server = *((SOCKFD *) serverfd);
    const size_t BUFFER_SIZE = MAX_ATOM_SIZE;
    unsigned char buffer[BUFFER_SIZE];
    struct sockaddr clientAddr;
    fprintf(stdout, "%sUDP server is listening for data%s\n", FG_GREEN, FG_RESET);

    pthread_t zmqThreads[MAX_ATOM_THREAD];
    int threadCount = 0;

    while (1) {

        socklen_t client_addr_len = sizeof(clientAddr);
        int recvLen = recvfrom(server, &buffer, BUFFER_SIZE, MSG_DONTWAIT, &clientAddr, &client_addr_len);
        if (recvLen < 0) {
            continue;
        }

        unsigned char *data = malloc(MAX_ATOM_SIZE);
        memcpy(data, buffer, MAX_ATOM_SIZE);
        pthread_create(&zmqThreads[threadCount], NULL, handle_atom, data);

        ++threadCount;
        if (threadCount >= MAX_ATOM_THREAD) {
            pthread_join(zmqThreads[threadCount % MAX_ATOM_THREAD], NULL);
            threadCount--;
        }

        memset(buffer, 0, MAX_ATOM_SIZE);
    }
}

_Noreturn void *beat_handler(void *data) {
    while (1) {
        queueZmqSendBytes(CFG_ZMQ_HEART_TOPIC, "", 0);
        pluginWatcher(0);

        struct timespec ts;
        ts.tv_sec = CFG_ZMQ_BEAT_INTERVAL / 1000;
        ts.tv_nsec = (CFG_ZMQ_BEAT_INTERVAL % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }
}

void connectionServerListen(SOCKFD server) {
    pthread_t thread;
    pthread_create(&thread, NULL, readFromSocket, (void *) &server);

    pthread_t threadSubscribe;
    pthread_create(&threadSubscribe, NULL, queueSubscribe, NULL);
    fprintf(stdout, "Listening for heartbeats on %s%s%s ZMQ topic\n", FG_CYAN, CFG_ZMQ_HEART_TOPIC, FG_RESET);

    pthread_t threadBeat;
    pthread_create(&threadBeat, NULL, beat_handler, NULL);

    pthread_t httpServerThread;
    pthread_create(&httpServerThread, NULL, startHttpServer, NULL);

    pthread_join(thread, NULL);
}

void internalPublish(void *data, size_t length) {
    int sockfd;
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1200);
    if (inet_aton("127.0.0.1", &server_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid address\n");
    }
    ssize_t bytes_sent = sendto(sockfd, data, length, 0,
                                (struct sockaddr *) &server_addr, sizeof(server_addr));
    close(sockfd);
}