#include "distance.h"

// ----------------------------------------------------------------------------------------

// Periodic boundary conditions (for position)
inline double PeriodicPos(double dr, double L) {

    double dr_new = dr - L * floor(dr / L);

    return dr_new;
}

// ----------------------------------------------------------------------------------------

// Periodic boundary conditions (for distance)
inline double PeriodicDis(double dr, double L) {

    double dr_new = dr - L * nearbyint(dr / L);

    return dr_new;
}

// ----------------------------------------------------------------------------------------

double Distance(Particle *p_i, Particle *p_j, double *rij) {
	
	double dissq = 0.;
	
	for (int d = 0; d < dim; d++) {
		rij[d] = PeriodicDis(p_j->r[d] - p_i->r[d], L);
		dissq += rij[d] * rij[d];
	}	
	
	return sqrt(dissq);
}

// ----------------------------------------------------------------------------------------