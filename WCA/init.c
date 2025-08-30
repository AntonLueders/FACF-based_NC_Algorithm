#include "init.h"
#include "distance.h"
#include "verletlist.h"

void InitRandom(Particle *P) {    

    long counter_overlap = 0;
    
    for (int i = 0; i < N; i++) {   
		
		if(counter_overlap > (long)N * (long)N) {
            printf("ERROR: System too dense.\n");
            exit(1);
        }
		
		for(int d = 0; d < dim; d++) {
            P[i].r_old[d] = 0.;
			P[i].f[d] = 0.;
			P[i].Noise[d] = 0.;
        }
		P[i].D = 1;
		P[i].sigma = 1;
		
        for (int d = 0; d < dim; d++) {
                
            P[i].r[d] = L * gsl_rng_uniform(generator);
		}
		
		double rij[dim];
		for (int j = 0; j < i; j++) {
            
			double disij = Distance(&(P[i]), &(P[j]), rij);     // See distance.c
            if(disij < (P[i].sigma + P[j].sigma) / 2.) {
                i--;
                counter_overlap++;
                break;
            }
        }         	
	}
	
	for(int i = 0; i < N; i++) {
		P[i].verList = malloc(sizeof(Node));
        P[i].verList->value = i;
        P[i].verList->next = NULL;
	}
	
	printf("Init. successful.\n");
}
