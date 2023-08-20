//
// Created by pedram on 6/11/23.
//

#ifndef LOGNET_ZMQPUBLISH_H
#define LOGNET_ZMQPUBLISH_H

#include <stddef.h>
#include <zmq.h>
#include "zmqConnection.h"

void queueZmqSendBytes(char *topic, void *data, size_t size);

#endif //LOGNET_ZMQPUBLISH_H
