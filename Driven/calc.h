#ifndef CALC_H
#define CALC_H

#include "HSBD.h"

void InitParametersCalcFACF(int *resolution, int *min_rate, double *a, double *e, int *n_min, int *n_max, int *t_samp, int steps);
void InitiSampleArraysCalcFACF(int n_max, int n_min, double a, double e, int **lengthF, int **rateF, int ***sample);
void InitStorageArraysFACF(int n_max, int *rateF, int N, int dim, unsigned long long **counter_FACF, double **facf, double **facf2, double **nfcf, double *****f0, double *****n0);
void CalcFACF(int n_max, int **sample, int *lengthF, int *rateF, double *facf, double *facf2, double *nfcf, double ****f0, double ****n0, unsigned long long *counter_FACF, Particle *P, int *t_samp);
void FreeMemoryFACF(int n_max, int **sample, int *lengthF, int *rateF, double *facf, double *facf2, double *nfcf, double ****f0, double ****n0);

#endif
