#include "headCache.h"
#include "config/bootstrap.h"
#include "utils/colors.h"

Atom_t *atomCache = 0;

void initializeAtomCache() {
    atomCache = malloc(sizeof(Atom_t) * CFG_ATOM_CACHE_HEAD_SIZE);
    for (int i = 0; i < CFG_ATOM_CACHE_HEAD_SIZE; i++) {
        EMPTY_ATOM(atomCache[i]);
    }
    fprintf(stdout, "Atom cache size %s%d%s atoms\n", FG_CYAN, CFG_ATOM_CACHE_HEAD_SIZE, FG_RESET);
}

void appendAtomCache(Atom_t atom) {
    EMPTY_ATOM(atomCache[CFG_ATOM_CACHE_HEAD_SIZE - 1]);
    for (int i = CFG_ATOM_CACHE_HEAD_SIZE - 1; i >= 0; i--) {
        if (i > 0) {
            atomCache[i] = atomCache[i - 1];
        } else {
            atomCache[i] = atom;
        }
    }
}