#include "zmqConnection.h"
#include "config/bootstrap.h"
#include "utils/colors.h"

void *zmqContext = 0;
void *zmqPublisher = 0;
void *zmqReply = 0;

void queueZmqCreateSocket() {
    zmqContext = zmq_ctx_new();
    zmqPublisher = zmq_socket(zmqContext, ZMQ_PUB);
    zmqReply = zmq_socket(zmqContext, ZMQ_REP);

    char connectionString[32];
    sprintf(connectionString, "tcp://*:%d", CFG_ZMQ_PORT);
    int rc = zmq_bind(zmqPublisher, connectionString);
    if (rc != 0) {
        fprintf(stderr, "ZMQ publisher binding error\n");
        exit(EXIT_FAILURE);
    }

    char connectionStringRouter[32];
    sprintf(connectionStringRouter, "tcp://*:%d", CFG_ZMQ_ROUTER_PORT);
    rc = zmq_bind(zmqReply, connectionStringRouter);
    if (rc != 0) {
        fprintf(stderr, "ZMQ router binding error\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "ZMQ publisher has been bind to port %s%d%s\n", FG_CYAN, CFG_ZMQ_PORT, FG_RESET);
    fprintf(stdout, "ZMQ reply has been bind to port %s%d%s\n", FG_CYAN, CFG_ZMQ_ROUTER_PORT, FG_RESET);
}