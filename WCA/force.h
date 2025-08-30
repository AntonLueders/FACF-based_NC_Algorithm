#ifndef FORCE_H
#define FORCE_H

#include "WCABD.h"

double CalcWCA(double sigmasq, double dijsq, double eps);
void CalcForce(Particle *P);

#endif
