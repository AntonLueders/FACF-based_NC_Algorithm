#ifndef PRINTDATA_H
#define PRINTDATA_H

#include "HSBD.h"

void PrintOvito(FILE *f, Particle *P, long step);
void PrintFACF(FILE *filename, long n_max, long *lengthF, double *facf, double *nfcf, unsigned long long *counter_FACF);

#endif