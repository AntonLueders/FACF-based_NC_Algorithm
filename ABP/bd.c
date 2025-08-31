#include "bd.h"
#include "distance.h"

// ----------------------------------------------------------------------------------------

void BrownianMotion(Particle *P) {

	for(int i = 0; i < N; i++) {
		
		for(int d = 0; d < dim; d++) {
			double Noise = sqrt(2. * P[i].D * dt) * gsl_ran_gaussian(generator, 1.0);
			P[i].r[d] += P[i].D * P[i].f[d] * dt + Noise;
			P[i].Noise[d] = Noise;
		}
		
		// Random angle displacement: sqrt(2 D_r t) with D_r = 3 D / sigma^2
		P[i].phi += sqrt(6. * P[i].D * dt / P[i].sigma / P[i].sigma) 
			* gsl_ran_gaussian(generator, 1.0);
	}
}

// ----------------------------------------------------------------------------------------