#include "verletlist.h"
#include "distance.h"

void GenerateVerletLists(Particle *P) {
	
	for (int i = 0; i < N; i++) {
		
		clearList(P[i].verList);
		double rij[dim];
		
		for (int j = 0; j < i; j++) {
			
			double disij = Distance(&(P[i]), &(P[j]), rij);     // See distance.c
		
			if (disij < (r_v + (P[i].sigma + P[j].sigma) / 2. + P[j].sigma / 2.)) {
				push(P[i].verList, P[j].verList->value);
				push(P[j].verList, P[i].verList->value);					
			}
		}
		
		for (int d = 0; d < dim; d++) {
			
			P[i].r_old[d] = P[i].r[d];
		}
	}
}

bool CheckVerlet(Particle *P) {
	
	double dissq_max[2] = {0., 0.};
	
	for (int i = 0; i < N; i++) {
	
		double dissq = 0.;
		double dr;
		
		for (int d = 0; d < dim; d++) {
			dr = PeriodicDis(P[i].r[d] - P[i].r_old[d], L);			
			dissq += dr * dr;
		}
		
		if (dissq > dissq_max[1]) {
			dissq_max[0] = dissq_max[1];
			dissq_max[1] = dissq;
		} else if (dissq > dissq_max[0]) {
			dissq_max[0] = dissq;
		}
	}
	
	return (sqrt(dissq_max[0]) + sqrt(dissq_max[1])) >= r_v;
}

void FreeVerLists(Particle *P) {

    for(int i = 0; i < N; i++) {
        clearList(P[i].verList);     // See lists.c
        free(P[i].verList);
    }
}
