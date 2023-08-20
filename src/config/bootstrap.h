//
// Created by pedram on 6/11/23.
//

#ifndef LOGNET_BOOTSTRAP_H
#define LOGNET_BOOTSTRAP_H

#include <stdlib.h>
#include <stdio.h>
#include <libconfig.h>
#include <stdbool.h>
#include <string.h>

extern int CFG_PORT;
extern int CFG_DEBUG;
extern int CFG_ZMQ_PORT;
extern int CFG_ZMQ_ROUTER_PORT;
extern char *CFG_ZMQ_HEART_TOPIC;
extern int CFG_ZMQ_BEAT_INTERVAL;
extern int CFG_HTTP_PORT;
extern char *CFG_HTTP_HOST;
extern int CFG_ATOM_CACHE_HEAD_SIZE;
extern int CFG_ATOM_BUFFER;


void bootstrapConfig(char *path);

#endif //LOGNET_BOOTSTRAP_H
