#include "bootstrap.h"

int CFG_PORT = 0;
int CFG_DEBUG = 0;
int CFG_ZMQ_PORT = 0;
int CFG_ZMQ_ROUTER_PORT = 0;
char *CFG_ZMQ_HEART_TOPIC = 0;
int CFG_ZMQ_BEAT_INTERVAL = 0;
char *CFG_HTTP_HOST = 0;
int CFG_HTTP_PORT = 0;
int CFG_ATOM_CACHE_HEAD_SIZE = 0;
int CFG_ATOM_BUFFER = 0;

void bootstrapConfig(char *path) {
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, path)) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }

    if (!config_lookup_int(&cfg, "PORT", &CFG_PORT))
        CFG_PORT = 1200;

    if (!config_lookup_bool(&cfg, "DEBUG", &CFG_DEBUG))
        CFG_DEBUG = false;

    if (!config_lookup_int(&cfg, "ZMQ_PORT", &CFG_ZMQ_PORT))
        CFG_ZMQ_PORT = 5555;

    if (!config_lookup_int(&cfg, "ZMQ_ROUTER_PORT", &CFG_ZMQ_ROUTER_PORT))
        CFG_ZMQ_ROUTER_PORT = 5556;

    const char *topicTemp;
    if (!config_lookup_string(&cfg, "ZMQ_HEART_TOPIC", &topicTemp)) {
        char *defaultTopic = "HEART";
        CFG_ZMQ_HEART_TOPIC = malloc(sizeof(strlen(defaultTopic)) + 1);
        strcpy(CFG_ZMQ_HEART_TOPIC, defaultTopic);
    }
    if (strlen(topicTemp) != 0) {
        CFG_ZMQ_HEART_TOPIC = malloc(strlen(topicTemp) + 1);
        strcpy(CFG_ZMQ_HEART_TOPIC, topicTemp);
    }

    if (!config_lookup_int(&cfg, "ZMQ_BEAT_INTERVAL", &CFG_ZMQ_BEAT_INTERVAL))
        CFG_ZMQ_BEAT_INTERVAL = 10000;

    if (!config_lookup_int(&cfg, "HTTP_PORT", &CFG_HTTP_PORT))
        CFG_HTTP_PORT = 8080;

    const char *httpHostDef;
    if (!config_lookup_string(&cfg, "HTTP_HOST", &httpHostDef)) {
        char *httpHost = "127.0.0.1";
        CFG_HTTP_HOST = malloc(sizeof(strlen(httpHost)) + 1);
        strcpy(CFG_HTTP_HOST, httpHost);
    }
    if (strlen(httpHostDef) != 0) {
        CFG_HTTP_HOST = malloc(strlen(httpHostDef) + 1);
        strcpy(CFG_HTTP_HOST, httpHostDef);
    }

    if (!config_lookup_int(&cfg, "ATOM_CACHE_HEAD_SIZE", &CFG_ATOM_CACHE_HEAD_SIZE))
        CFG_ATOM_CACHE_HEAD_SIZE = 16;

    if (!config_lookup_int(&cfg, "ATOM_BUFFER", &CFG_ATOM_BUFFER))
        CFG_ATOM_BUFFER = 128;

    config_destroy(&cfg);
}