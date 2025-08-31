#include "calc.h"

// ----------------------------------------------------------------------------------------

// The following functions are just for the initialization of the algorithm to calculate
// the correlation function

void InitParametersCalcFACF(int *resolution, int *min_rate, double *a, double *e, 
		int *n_min, int *n_max, int *t_samp, int steps) {
	
    *resolution = 15;
    *min_rate = 10;
    *a = pow(10., 1. / (double)(*resolution));
    *e = log((double)(*min_rate)) / log((double)steps);
    *n_min = (int)(-log(*a - 1) / log(*a)) + 1;
	*n_max = (int)(log((double)steps) / log(*a));
	*n_max -= *n_min;
    *t_samp = 0;
}

// ----------------------------------------------------------------------------------------

void InitiSampleArraysCalcFACF(int n_max, int n_min, double a, double e, 
		int **lengthF, int **rateF, int ***sample) {
	
    *lengthF = malloc(n_max * sizeof(int));
    *rateF = malloc(n_max * sizeof(int));
    *sample = malloc(n_max * sizeof(int*));

    for (int n = 0; n < n_max; n++) {
        (*lengthF)[n] = (int)(pow(a, n + 1. + n_min) - pow(a, n_min));
        (*rateF)[n] = (int)(ceil(pow((*lengthF)[n], e)));
        (*sample)[n] = malloc((*rateF)[n] * sizeof(int));

        for (int nn = 0; nn < (*rateF)[n]; nn++) {
            (*sample)[n][nn] = (*lengthF)[n] * nn / (*rateF)[n];
        }
    }
}

// ----------------------------------------------------------------------------------------

void InitStorageArraysFACF(int n_max, int *rateF, int N, int dim, 
		unsigned long long **counter_FACF, double **facf, double **facf2, double **nfcf, 
		double *****f0, double *****n0) {
	
    *counter_FACF = malloc(n_max * sizeof(unsigned long long));
    *facf = malloc(n_max * sizeof(double));
	*facf2 = malloc(n_max * sizeof(double));
	*nfcf = malloc(n_max * sizeof(double)); 
    *f0 = malloc(n_max * sizeof(double***));
	*n0 = malloc(n_max * sizeof(double***));

    if (*f0 == NULL) {
        fprintf(stderr, "ERROR at f0\n");
        exit(EXIT_FAILURE);
    }
	if (*n0 == NULL) {
        fprintf(stderr, "ERROR at n0\n");
        exit(EXIT_FAILURE);
    }

    for (int n = 0; n < n_max; n++) {
        (*counter_FACF)[n] = 0;
        (*facf)[n] = 0.;
		(*facf2)[n] = 0.;
		(*nfcf)[n] = 0.;

        (*f0)[n] = malloc(rateF[n] * sizeof(double**));
        if ((*f0)[n] == NULL) {
            fprintf(stderr, "ERROR at f0[%d]\n", n);
            exit(EXIT_FAILURE);
        }
	    (*n0)[n] = malloc(rateF[n] * sizeof(double**));
        if ((*n0)[n] == NULL) {
            fprintf(stderr, "ERROR at n0[%d]\n", n);
            exit(EXIT_FAILURE);
        }

        for (int nn = 0; nn < rateF[n]; nn++) {
			
            (*f0)[n][nn] = malloc(N * sizeof(double*));
            if ((*f0)[n][nn] == NULL) {
                fprintf(stderr, "ERROR at f0[%d][%d]\n", n, nn);
                exit(EXIT_FAILURE);
            }
			(*n0)[n][nn] = malloc(N * sizeof(double*));
            if ((*n0)[n][nn] == NULL) {
                fprintf(stderr, "ERROR at n0[%d][%d]\n", n, nn);
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < N; i++) {
				
                (*f0)[n][nn][i] = malloc(dim * sizeof(double));
                if ((*f0)[n][nn][i] == NULL) {
                    fprintf(stderr, "ERROR at f0[%d][%d][%d]\n", n, nn, i);
                    exit(EXIT_FAILURE);
                }
				(*n0)[n][nn][i] = malloc(dim * sizeof(double));
                if ((*n0)[n][nn][i] == NULL) {
                    fprintf(stderr, "ERROR at n0[%d][%d][%d]\n", n, nn, i);
                    exit(EXIT_FAILURE);
                }

                for (int d = 0; d < dim; d++) {
                    (*f0)[n][nn][i][d] = 0.;
					(*n0)[n][nn][i][d] = 0.;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------------------

// Calculates the correlation function. 
// For more infos see Siems et al. J. Phys. Conf. Ser. 2018 or
// http://nbn-resolving.de/urn:nbn:de:bsz:352-0-419804
void CalcFACF(int n_max, int **sample, int *lengthF, int *rateF, double *facf, 
		double *facf2, double *nfcf, double ****f0, double ****n0, 
		unsigned long long *counter_FACF, Particle *P, int *t_samp) {

    for (int n = 0; n < n_max; n++) {
        for (int nn = 0; nn < rateF[n]; nn++) {
            if (*t_samp % lengthF[n] == sample[n][nn]) {
                if (*t_samp > sample[n][nn]) {
                    for (int i = 0; i < N; i++) {
                        for (int d = 0; d < dim; d++) {
                            facf[n] += P[i].f[d] * f0[n][nn][i][d];
							if (d == 0) {
							   facf2[n] += (P[i].f[d] + force) * (f0[n][nn][i][d] + force);
							   nfcf[n] += (P[i].f[d] + force) * n0[n][nn][i][d];
							} else {
							   facf2[n] += P[i].f[d] * f0[n][nn][i][d];
							   nfcf[n] += P[i].f[d] * n0[n][nn][i][d];							
							}
                        }
                        counter_FACF[n]++;
                    }
                }
            }
        }
    }

    for (int n = 0; n < n_max; n++) {
        for (int nn = 0; nn < rateF[n]; nn++) {
            if (*t_samp % lengthF[n] == sample[n][nn]) {
                for (int i = 0; i < N; i++) {
                    for (int d = 0; d < dim; d++) {
                        f0[n][nn][i][d] = P[i].f[d];
						n0[n][nn][i][d] = P[i].Noise[d];
                    }
                }
            }
        }
    }

    (*t_samp)++;
}

// ----------------------------------------------------------------------------------------

void FreeMemoryFACF(int n_max, int **sample, int *lengthF, int *rateF, double *facf, 
		double *facf2, double *nfcf, double ****f0, double ****n0) {
 
    for (int n = 0; n < n_max; n++) {
        free(sample[n]);
    }
    free(sample);

    free(lengthF);
    free(facf);
	free(facf2);
	free(nfcf);

    for (int n = 0; n < n_max; n++) {
        for (int nn = 0; nn < rateF[n]; nn++) {
            for (int i = 0; i < N; i++) {
                free(f0[n][nn][i]); 
				free(n0[n][nn][i]); 
            }
            free(f0[n][nn]); 
			free(n0[n][nn]);
        }
        free(f0[n]); 
		free(n0[n]);
    }
    free(f0); 
	free(n0);
	
	free(rateF);
}

// ----------------------------------------------------------------------------------------