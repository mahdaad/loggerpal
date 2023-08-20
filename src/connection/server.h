#ifndef CONNECTION_SERVER_H
#define CONNECTION_SERVER_H

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <memory.h>
#include <pthread.h>
#include "models/atom.h"
#include <stddef.h>

#define SOCKFD int

extern Atom_t **__buffer;
extern size_t __buffer_pointer;

#define COPY_ATOM_FIELD(atom, source, offset, field) \
atom->field = malloc(atom->field##_length + 1);\
memcpy(atom->field, source + offset, atom->field##_length);\
atom->field[atom->field##_length] = '\0';\
offset += atom->field##_length

SOCKFD connectionServerCreate(int port);

void connectionServerListen(SOCKFD server);

void internalPublish(void *data, size_t length);

#endif //CONNECTION_SERVER_H