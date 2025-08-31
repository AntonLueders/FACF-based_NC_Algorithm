#include "force.h"
#include "distance.h"

// ----------------------------------------------------------------------------------------

// Effective propulsion force and harmonic trap
void CalcForce(Particle *P) {
	
	for(int i = 0; i < N; i++) {
		for (int d = 0; d < dim; d++) {
			P[i].f[d] = 0.;
		}		
	}
	
	for(int i = 0; i < N; i++) {
		
		P[i].f[0] = force * cos(P[i].phi) - 1. * P[i].r[0];
		P[i].f[1] = force * sin(P[i].phi) - 1. * P[i].r[1];
	}
}

// ----------------------------------------------------------------------------------------