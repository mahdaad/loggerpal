#include "pluginRegistry.h"
#include "config/bootstrap.h"
#include "utils/colors.h"
#include <stdio.h>

Plugin_t PluginRegistry[MAX_PLUGIN_NUMBER] = {};

unsigned int hash(char *key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // djb2 hash function
    }
    return hash % MAX_PLUGIN_NUMBER;
}

void pluginPrepareRegistry() {
    for (unsigned int index = 0; index < MAX_PLUGIN_NUMBER; index++) {
        EMPTY_PLUGIN(PluginRegistry[index]);
    }
}

void pluginRegistryPut(Plugin_t plugin) {
    unsigned int index = hash(plugin.id);
    if (pluginRegistryGet(plugin.id)->lastBeat == 0) {
        if (CFG_DEBUG == 1) {
            printf("%s%s%s(%s%s%s) is %sregistered%s\n", FG_PURPLE, plugin.name, FG_RESET, FG_YELLOW,
                   plugin.id, FG_RESET, FG_GREEN, FG_RESET);
        }
    }
    PluginRegistry[index] = plugin;
}

Plugin_t *pluginRegistryGet(char *id) {
    unsigned int index = hash(id);
    return &PluginRegistry[index];
}

void pluginRegistryDel(char *id) {
    unsigned int index = hash(id);
    if (CFG_DEBUG == 1) {
        printf("%s%s%s(%s%s%s) is %sunregistered%s\n", FG_PURPLE, PluginRegistry[index].name, FG_RESET, FG_YELLOW,
               PluginRegistry[index].id, FG_RESET, FG_RED, FG_RESET);
    }
    EMPTY_PLUGIN(PluginRegistry[index]);
}

unsigned int pluginRegistryGetActives(Plugin_t ***buffer) {
    unsigned int count = 0;
    *buffer = malloc(sizeof(Plugin_t *) * count);
    for (unsigned int index = 0; index < MAX_PLUGIN_NUMBER; index++) {
        if (PluginRegistry[index].lastBeat == 0) {
            continue;
        }
        *buffer = (Plugin_t **) realloc(*buffer, sizeof(Plugin_t *) * ++count);
        (*buffer)[count - 1] = &PluginRegistry[index];
    }
    return count;
}