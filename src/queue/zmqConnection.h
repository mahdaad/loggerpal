//
// Created by pedram on 6/11/23.
//

#ifndef LOGNET_ZMQCONNECTION_H
#define LOGNET_ZMQCONNECTION_H

#include <zmq.h>

extern void* zmqContext;
extern void* zmqPublisher;
extern void* zmqReply;

void queueZmqCreateSocket();

#endif //LOGNET_ZMQCONNECTION_H
