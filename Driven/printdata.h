#ifndef PRINTDATA_H
#define PRINTDATA_H

#include "HSBD.h"

void PrintOvito(FILE *f, Particle *P, int step);
void PrintFACF(FILE *filename, int n_max, int *lengthF, double *facf, double *facf2, double *nfcf, unsigned long long *counter_FACF);

#endif