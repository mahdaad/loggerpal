#include <time.h>
#include "pluginWatcher.h"
#include "config/bootstrap.h"
#include "pluginRegistry.h"
#include "utils/colors.h"

void *pluginWatcher(void *data) {
    Plugin_t **plugins = 0;
    unsigned int num = pluginRegistryGetActives(&plugins);
    if (num == 0) return 0;
    for (unsigned int i = 0; i < num; i++) {
        time_t currentTime = time(NULL);
        unsigned int utcTimestamp = (unsigned int) currentTime;
        utcTimestamp -= CFG_ZMQ_BEAT_INTERVAL / 1000;

        if (utcTimestamp > plugins[i]->lastBeat) {

            pluginRegistryDel(plugins[i]->id);
        }
    }
    return 0;
}