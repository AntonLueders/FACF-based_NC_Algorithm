#ifndef VERLETLIST_H
#define VERLETLIST_H

#include "WCABD.h"
#include "lists.h"

void GenerateVerletLists(Particle *P);
bool CheckVerlet(Particle *P);
void FreeVerLists(Particle *P);

#endif
