#ifndef CALC_H
#define CALC_H

#include "ABPBD.h"

void InitParametersCalcFACF(int *resolution, int *min_rate, double *a, double *e, int *n_min, long *n_max, long *t_samp, long steps);
void InitiSampleArraysCalcFACF(long n_max, int n_min, double a, double e, long **lengthF, long **rateF, long ***sample);
void InitStorageArraysFACF(long n_max, long *rateF, int N, int dim, unsigned long long **counter_FACF, double **facf, double **nfcf, double *****f0, double *****n0);
void CalcFACF(long n_max, long **sample, long *lengthF, long *rateF, double *facf, double *nfcf, double ****f0, double ****n0, unsigned long long *counter_FACF, Particle *P, long *t_samp);
void FreeMemoryFACF(long n_max, long **sample, long *lengthF, long *rateF, double *facf, double *nfcf, double ****f0, double ****n0);

#endif
