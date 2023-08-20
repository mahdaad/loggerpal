//
// Created by pedram on 6/14/23.
//

#ifndef LOGNET_HEADCACHE_H
#define LOGNET_HEADCACHE_H

#include "models/atom.h"

extern Atom_t *atomCache;

void initializeAtomCache();
void appendAtomCache(Atom_t atom);

#endif //LOGNET_HEADCACHE_H
