#ifndef MODELS_ATOM_H
#define MODELS_ATOM_H

#include <stdlib.h>
#include <stdio.h>

#define ATOM_HEAD 'p'
/*
 * I wonder why "p"?
 *                  - Pedram Dehghanpour :)
 */

#define EMPTY_ATOM(atom) memset(&atom, 0, sizeof(Atom_t))

typedef enum {
    INFO = 1,
    ERROR = 2,
    DEBUG = 3,
    TEST = 4,
} AtomType_t;

typedef enum {
    VERY_LOW = 1,
    LOW = 2,
    NORMAL = 3,
    HIGH = 4,
    VERY_HIGH = 5
} AtomLevel;

typedef struct {
    unsigned char head;
    unsigned char type;
    unsigned char level;
    unsigned int time;
    unsigned int namespace_length;
    unsigned int section_length;
    unsigned int key_length;
    unsigned int value_length;
    unsigned int id_length;
    unsigned int nid_length;
    char *namespace;
    char *section;
    char *key;
    char *value;
    char *id;
    char *nid;
} Atom_t;

void atomPrint(Atom_t *atom);

void atomFree(Atom_t *atom);

size_t atomSerialize(unsigned char **output, Atom_t *atom);
Atom_t *atomFromBuffer(unsigned char *buffer);

#endif