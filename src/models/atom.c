#include "atom.h"
#include "utils/colors.h"
#include "utils/timeUtils.h"
#include "utils/debug.h"
#include "connection/server.h"
#include <string.h>
#include <malloc.h>

void atomPrint(Atom_t *data) {
    if (data->head != ATOM_HEAD) {
        return;
    }
    unsigned char type = data->type;
    unsigned char level = data->level;
    unsigned int time = data->time;
    char *key = data->key;
    char *namespace = data->namespace;
    char *section = data->section;
    char *value = data->value;
    char *id = data->id;
    char *nid = data->nid;

    char *typeString = 0;
    if (type == INFO) {
        char *_s = "INFO";
        typeString = malloc(strlen(_s) + 1);
        strcpy(typeString, _s);
    } else if (type == ERROR) {
        char *_s = "ERROR";
        typeString = malloc(strlen(_s) + 1);
        strcpy(typeString, _s);
    } else if (type == DEBUG) {
        char *_s = "DEBUG";
        typeString = malloc(strlen(_s) + 1);
        strcpy(typeString, _s);
    } else if (type == TEST) {
        char *_s = "TEST";
        typeString = malloc(strlen(_s) + 1);
        strcpy(typeString, _s);
    } else {
        char *_s = "UNKNOWN";
        typeString = malloc(strlen(_s) + 1);
        strcpy(typeString, _s);
    }

    char *levelString = 0;
    if (level == VERY_LOW) {
        char *_s = "VERY_LOW";
        levelString = malloc(strlen(_s) + 1);
        strcpy(levelString, _s);
    } else if (level == LOW) {
        char *_s = "LOW";
        levelString = malloc(strlen(_s) + 1);
        strcpy(levelString, _s);
    } else if (level == NORMAL) {
        char *_s = "NORMAL";
        levelString = malloc(strlen(_s) + 1);
        strcpy(levelString, _s);
    } else if (level == HIGH) {
        char *_s = "HIGH";
        levelString = malloc(strlen(_s) + 1);
        strcpy(levelString, _s);
    } else if (level == VERY_HIGH) {
        char *_s = "VERY_HIGH";
        levelString = malloc(strlen(_s) + 1);
        strcpy(levelString, _s);
    } else {
        char *_s = "UNKNOWN_LEVEL";
        levelString = malloc(strlen(_s) + 1);
        strcpy(levelString, _s);
    }

    char timeStr[20];
    convertTimestamp(time, timeStr, sizeof(timeStr));

    int freeNid = 0;
    if (strlen(nid) == 0) {
        char *nothing = "(nothing)";
        nid = malloc(strlen(nothing) + 1);
        strcpy(nid, nothing);
        freeNid = 1;
    }

    fprintf(stdout, "%s%s%s (%s%s%s)\t%s%s%s(%s%s%s)\t%s%s%s\t%s%s%s %s=>%s %s%s%s\t%s%s%s%s(%s%s%s%s%s)%s\n", FG_CYAN,
            namespace,
            FG_RESET, FG_YELLOW, section, FG_RESET, FG_PURPLE, typeString, FG_RESET, FG_WHITE, levelString, FG_RESET,
            FG_YELLOW,
            timeStr, FG_RESET, FG_BLUE, id, FG_RESET, FG_WHITE, FG_RESET, FG_RED, nid, FG_RESET, FG_GREEN, key,
            FG_RESET, FG_GREEN,
            FG_RESET, FG_CYAN, value,
            FG_RESET, FG_GREEN, FG_RESET);

    free(typeString);
    free(levelString);
    if (freeNid == 1) {
        free(nid);
    }
}

void atomFree(Atom_t *atom) {
    free(atom->namespace);
    free(atom->section);
    free(atom->key);
    free(atom->value);
    free(atom->id);
    free(atom->nid);
    free(atom);
}



size_t atomSerialize(unsigned char **output, Atom_t *atom) {

    size_t length = 1 + 1 + 1 + (4 * 7);
    *output = (unsigned char *) malloc(length);

    memcpy(*output, &(atom->head), sizeof(atom->head));
    memcpy(*output + 1, &(atom->type), sizeof(atom->type));
    memcpy(*output + 2, &(atom->level), sizeof(atom->level));
    memcpy(*output + 3, &(atom->time), sizeof(atom->time));
    memcpy(*output + 7, &(atom->namespace_length), sizeof(atom->namespace_length));
    memcpy(*output + 11, &(atom->section_length), sizeof(atom->section_length));
    memcpy(*output + 15, &(atom->key_length), sizeof(atom->key_length));
    memcpy(*output + 19, &(atom->value_length), sizeof(atom->value_length));
    memcpy(*output + 23, &(atom->id_length), sizeof(atom->id_length));
    memcpy(*output + 27, &(atom->nid_length), sizeof(atom->nid_length));

    length += atom->namespace_length;
    *output = realloc(*output, length);
    memcpy(*output + length - atom->namespace_length, atom->namespace, atom->namespace_length);

    length += atom->section_length;
    *output = realloc(*output, length);
    memcpy(*output + length - atom->section_length, atom->section, atom->section_length);

    length += atom->key_length;
    *output = realloc(*output, length);
    memcpy(*output + length - atom->key_length, atom->key, atom->key_length);

    length += atom->value_length;
    *output = realloc(*output, length);
    memcpy(*output + length - atom->value_length, atom->value, atom->value_length);

    length += atom->id_length;
    *output = realloc(*output, length);
    memcpy(*output + length - atom->id_length, atom->id, atom->id_length);

    length += atom->nid_length;
    *output = realloc(*output, length);
    memcpy(*output + length - atom->nid_length, atom->nid, atom->nid_length);

    return length;
}

Atom_t *atomFromBuffer(unsigned char *buffer){
    Atom_t *atom = malloc(sizeof(Atom_t));

    memcpy(&(atom->head), buffer, 1);
    memcpy(&(atom->type), buffer + 1, 1);
    memcpy(&(atom->level), buffer + 2, 1);
    memcpy(&(atom->time), buffer + 3, 4);
    memcpy(&(atom->namespace_length), buffer + 7, 4);
    memcpy(&(atom->section_length), buffer + 11, 4);
    memcpy(&(atom->key_length), buffer + 15, 4);
    memcpy(&(atom->value_length), buffer + 19, 4);
    memcpy(&(atom->id_length), buffer + 23, 4);
    memcpy(&(atom->nid_length), buffer + 27, 4);

    size_t offset = offsetof(Atom_t, namespace) - 1;

    COPY_ATOM_FIELD(atom, buffer, offset, namespace);
    COPY_ATOM_FIELD(atom, buffer, offset, section);
    COPY_ATOM_FIELD(atom, buffer, offset, key);
    COPY_ATOM_FIELD(atom, buffer, offset, value);
    COPY_ATOM_FIELD(atom, buffer, offset, id);
    COPY_ATOM_FIELD(atom, buffer, offset, nid);

    return atom;
}