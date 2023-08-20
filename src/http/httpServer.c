#include "httpServer.h"
#include "utils/colors.h"
#include "plugin/pluginRegistry.h"
#include "models/atom.h"
#include "headCache/headCache.h"
#include "utils/debug.h"
#include "connection/server.h"

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    char *headers = "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\nAccess-Control-Allow-Headers: *\r\n";
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_http_match_uri(hm, "/ping")) {


            mg_http_reply(c, 200, headers, "{%m:%d,%m:{},%m:%m}\n",
                          MG_ESC("code"), 200, MG_ESC("data"), MG_ESC("message"), MG_ESC("PONG"));


        } else if (mg_http_match_uri(hm, "/api/plugins")) {


            Plugin_t **plugins = 0;
            unsigned int num = pluginRegistryGetActives(&plugins);

            char *json_buffer;
            if (num > 0) {
                int json_size = (ID_LENGTH + NAME_LENGTH + 32) * num;
                json_buffer = malloc(json_size);
                int offset = 0;
                offset += snprintf(json_buffer + offset, json_size - offset, "[");
                for (unsigned int i = 0; i < num; i++) {
                    offset += snprintf(json_buffer + offset, json_size - offset,
                                       "{\"id\":\"%s\",\"name\":\"%s\",\"lastBeat\":%u}",
                                       plugins[i]->id, plugins[i]->name, plugins[i]->lastBeat);
                    if (i < num - 1) {
                        offset += snprintf(json_buffer + offset, json_size - offset, ",");
                    }
                }
                offset += snprintf(json_buffer + offset, json_size - offset, "]");
            } else {
                char *tmp = "[]";
                json_buffer = malloc(3);
                strcpy(json_buffer, tmp);
            }

            mg_http_reply(c, 200, headers, "{%m:%d,%m:{%m:%d, %m:%s},%m:%m}\n",
                          MG_ESC("code"), 200, MG_ESC("data"), MG_ESC("count"), num, MG_ESC("plugins"),
                          json_buffer, MG_ESC("message"), MG_ESC(""));

            free(json_buffer);
            free(plugins);
        } else if (mg_http_match_uri(hm, "/api/send")) {
            mg_http_reply(c, 201, headers, "");
            internalPublish((void *) hm->body.ptr, hm->body.len);
        } else if (mg_http_match_uri(hm, "/api/cache")) {

            char *json_buffer;
            if (CFG_ATOM_CACHE_HEAD_SIZE > 0) {
                size_t json_size = sizeof(Atom_t) * CFG_ATOM_CACHE_HEAD_SIZE;
                json_buffer = malloc(json_size);
                int offset = 0;
                offset += snprintf(json_buffer + offset, json_size - offset, "[");
                for (unsigned int i = 0; i < CFG_ATOM_CACHE_HEAD_SIZE; i++) {
                    offset += snprintf(json_buffer + offset, json_size - offset,
                                       "{\"head\":\"%d\",\"type\":\"%d\",\"level\":%d,\"time\":%d,\"namespace\":\"%s\",\"section\":\"%s\",\"key\":\"%s\",\"value\":\"%s\",\"id\":\"%s\",\"nid\":\"%s\"}",
                                       atomCache[i].head, atomCache[i].type, atomCache[i].level, atomCache[i].time,
                                       atomCache[i].namespace, atomCache[i].section, atomCache[i].key,
                                       atomCache[i].value, atomCache[i].id, atomCache[i].nid);
                    if (i < CFG_ATOM_CACHE_HEAD_SIZE - 1) {
                        offset += snprintf(json_buffer + offset, json_size - offset, ",");
                    }
                }
                offset += snprintf(json_buffer + offset, json_size - offset, "]");
            } else {
                char *tmp = "[]";
                json_buffer = malloc(3);
                strcpy(json_buffer, tmp);
            }

            mg_http_reply(c, 200, headers, "{%m:%d,%m:%s,%m:%m}\n",
                          MG_ESC("code"), 200, MG_ESC("data"), json_buffer, MG_ESC("message"), MG_ESC(""));

            free(json_buffer);


        } else {


            mg_http_reply(c, 200, headers, "{%m:%d,%m:{},%m:%m}\n",
                          MG_ESC("code"), 404, MG_ESC("data"), MG_ESC("message"), MG_ESC("Requested URL not found"));


        }
    }
}

_Noreturn void *startHttpServer(void *data) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    char connection[64];
    sprintf(connection, "http://%s:%d", CFG_HTTP_HOST, CFG_HTTP_PORT);
    fprintf(stdout, "HTTP server is running %s%s%s\n", FG_CYAN, connection, FG_RESET);
    mg_http_listen(&mgr, connection, fn, NULL);
    for (;;) mg_mgr_poll(&mgr, 1000);
}