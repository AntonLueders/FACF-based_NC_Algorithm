#include "force.h"
#include "distance.h"

double CalcWCA(double sigmasq, double dijsq, double eps) {

    double inv_rsq_eff = sigmasq / dijsq;
    return 48. * eps / sigmasq * (pow(inv_rsq_eff, 7.) - 0.5 * pow(inv_rsq_eff, 4.));
}

void CalcForce(Particle *P) {
	
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
				if(dis < pow(2., 1. / 6.) * (P[i].sigma + P[j].sigma) / 2.) {
				
					double fp = CalcWCA(pow((P[i].sigma + P[j].sigma) / 2., 2.), dis * dis, 1.0);
					
					for(int d = 0; d < dim; d++) {
						
						  
						P[i].f[d] -= fp * rij[d];
						P[j].f[d] += fp * rij[d];
					}
				}
			}
			
			current = current->next;
		} 
	}
}