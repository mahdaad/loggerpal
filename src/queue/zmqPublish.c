#include "zmqPublish.h"
#include <string.h>

void queueZmqSendBytes(char *topic, void *data, size_t size){
    zmq_send(zmqPublisher, topic, strlen(topic), ZMQ_SNDMORE);
    zmq_send(zmqPublisher, data, size, 0);
}