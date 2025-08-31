#include "init.h"
#include "distance.h"

// ----------------------------------------------------------------------------------------

void InitRandom(Particle *P) {    
    
    for (int i = 0; i < N; i++) {   
		
		for(int d = 0; d < dim; d++) {
            P[i].r_old[d] = 0.;
			P[i].f[d] = 0.;
			P[i].Noise[d] = 0.;
        }
		P[i].D = 1;
		P[i].sigma = 1;
		
        for (int d = 0; d < dim; d++) {
                
            P[i].r[d] = 0.;
			
		}
		P[i].phi = 2. * M_PI * gsl_rng_uniform(generator);       	
	}
	
	for(int i = 0; i < N; i++) {
		P[i].verList = malloc(sizeof(Node));
        P[i].verList->value = i;
        P[i].verList->next = NULL;
	}
	
	printf("Init. successful.\n");
}

// ----------------------------------------------------------------------------------------

void FreeVerLists(Particle *P) {

    for(int i = 0; i < N; i++) {
        clearList(P[i].verList);     // See lists.c
        free(P[i].verList);
    }
}

// ----------------------------------------------------------------------------------------
