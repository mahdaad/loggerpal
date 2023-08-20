#include "zmqReply.h"
#include "models/plugin.h"
#include "plugin/pluginRegistry.h"

_Noreturn void *queueSubscribe(void *data) {
    while (1) {
        // Receive topic (envelope)
        char topic[256];
        int identityLength = zmq_recv(zmqReply, topic, sizeof(topic) - 1, 0);
        if (identityLength == -1) {
            continue;
        }
        topic[identityLength] = '\0';

        // Receive message from client
        Plugin_t buffer;
        int messageLength = zmq_recv(zmqReply, &buffer, sizeof(Plugin_t) , 0);
        if (messageLength == -1) {
            continue;
        }

        pluginRegistryPut(buffer);

        if(strcmp(topic, CFG_ZMQ_HEART_TOPIC) == 0) {
            char response[256];
            sprintf(response, "HEARTBEAT RECEIVED");
            zmq_send(zmqReply, response, strlen(response), 0);
        }
    }
}