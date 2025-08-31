#include "printdata.h"

// ----------------------------------------------------------------------------------------

void PrintOvito(FILE *f, Particle *P, int step) {
    
    fprintf(f, "%d\n", N);
    fprintf(f, "step = %d\n", step + 1);
	
	if (dim == 1) {
		for (int i = 0; i < N; i++) {
		
			fprintf(f, "s1\t%f\t%f\t%f\n", P[i].r[0], 0., 0.);
		}
	} else if (dim == 2) {
		for (int i = 0; i < N; i++) {
		
			fprintf(f, "s1\t%f\t%f\t%f\n", P[i].r[0], P[i].r[1], 0.);
		}		
	} else if (dim == 3) {
		for (int i = 0; i < N; i++) {
		
			fprintf(f, "s1\t%f\t%f\t%f\n", P[i].r[0], P[i].r[1], P[i].r[2]);
		}
	}
}

// ----------------------------------------------------------------------------------------

void PrintFACF(FILE *filename, int n_max, int *lengthF, double *facf, double *facf2, 
		double *nfcf, unsigned long long *counter_FACF) {

    for (int n = 0; n < n_max; n++) {
        unsigned long long counter_check = counter_FACF[n];
        if (counter_check == 0) {
            counter_check = 1;
        }
        fprintf(filename, "%f\t%2.14f\t%2.14f\t%2.14f\n", (double)lengthF[n] * dt, 
			facf[n] / (double)counter_check, facf2[n] / (double)counter_check, 
			nfcf[n] / (double)counter_check / dt);
    }
}

// ----------------------------------------------------------------------------------------