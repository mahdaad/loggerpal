#include <stdio.h>
#include "connection/server.h"
#include "config/bootstrap.h"
#include "queue/zmqConnection.h"
#include "headCache/headCache.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Config path parameter is required\n");
        exit(EXIT_FAILURE);
    }
    bootstrapConfig(argv[1]);

    SOCKFD server = connectionServerCreate(CFG_PORT);
    queueZmqCreateSocket();
    initializeAtomCache();

    connectionServerListen(server);
    return 0;
}