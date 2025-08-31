#include "bd.h"
#include "distance.h"

// ----------------------------------------------------------------------------------------

// Brownian motion and drive
void BrownianMotion(Particle *P) {

	for(int i = 0; i < N; i++) {
		
		for(int d = 0; d < dim; d++) {
			double Noise = sqrt(2. * P[i].D * dt) * gsl_ran_gaussian(generator, 1.0);
			P[i].r[d] += Noise;
			if (d == 0) {
				P[i].r[d] += P[i].D / T * force * dt; // Drive
			}
			P[i].r[d] = PeriodicPos(P[i].r[d], L);
			P[i].Noise[d] = Noise;
		}
	}
}

// ----------------------------------------------------------------------------------------
	
void CollsionAvoidance(Particle *P) {
	
	for(int i = 0; i < N; i++) {
		for (int d = 0; d < dim; d++) {
			P[i].f[d] = 0.;
		}		
	}
	
	for(int i = 0; i < N; i++) {
		
		Node *current = P[i].verList->next;
		while (current != NULL) {
			
			int j = current->value;
			
			if (j < i) {
			
				double rij[dim];
				double dis = Distance(&(P[i]), &(P[j]), rij);
				if(dis < (P[i].sigma + P[j].sigma) / 2.) {
					for(int d = 0; d < dim; d++) {
						
						P[i].r[d] += 0.5 * (dis - 0.5 * (P[i].sigma + P[j].sigma)) * rij[d] / dis;
						P[j].r[d] -= 0.5 * (dis - 0.5 * (P[i].sigma + P[j].sigma)) * rij[d] / dis;
						
						P[i].r[d] = PeriodicPos(P[i].r[d], L);
						P[j].r[d] = PeriodicPos(P[j].r[d], L);
						
						P[i].f[d] += T / P[i].D * 0.5 * (dis - 0.5 * (P[i].sigma + P[j].sigma)) * rij[d] / (dt * dis);
						P[j].f[d] -= T / P[j].D * 0.5 * (dis - 0.5 * (P[i].sigma + P[j].sigma)) * rij[d] / (dt * dis);
					}
				}
			}
			
			current = current->next;
		} 
	}
}

// ----------------------------------------------------------------------------------------