//
// Created by pedram on 6/12/23.
//

#ifndef LOGNET_PLUGINREGISTRY_H
#define LOGNET_PLUGINREGISTRY_H

#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include "models/plugin.h"

#define MAX_PLUGIN_NUMBER 1024

#define IS_PLUGIN_EMPTY(plugin) plugin.lastBeat == 0
#define EMPTY_PLUGIN(plugin)  memset(plugin.id, 0, ID_LENGTH);memset(plugin.name, 0, NAME_LENGTH);plugin.lastBeat=0


// It's a hashtable
extern Plugin_t PluginRegistry[MAX_PLUGIN_NUMBER];

void pluginPrepareRegistry();

void pluginRegistryPut(Plugin_t plugin);

Plugin_t *pluginRegistryGet(char *id);

void pluginRegistryDel(char *id);

unsigned int pluginRegistryGetActives(Plugin_t ***buffer);

#endif //LOGNET_PLUGINREGISTRY_H
