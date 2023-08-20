//
// Created by pedram on 6/13/23.
//

#ifndef LOGNET_PLUGIN_H
#define LOGNET_PLUGIN_H

#define ID_LENGTH 64
#define NAME_LENGTH 64

typedef struct {
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    unsigned int lastBeat;
} Plugin_t;

#endif //LOGNET_PLUGIN_H
