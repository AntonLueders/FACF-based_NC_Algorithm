#ifndef NpT_2D_R_H
#define NpT_2D_R_H

#include "lists.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_sf_log.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DIM 3
#define NP 500
#define DDD 1
#define TEMP 1.
#define STEPS 100000
#define RATE 100
#define SIGMA 1
#define SEED 1
#define DT 0.00001
#define RV 1.55
#define LL 20

// Definition of bool-variables
typedef enum { false, true } bool;

// Structure which manages the particle information
struct particle {
    double r[DIM]; // Position 
    double r_old[DIM];
	double f[DIM];
	double Noise[DIM];
    double D;
	double sigma;
    Node *verList; // Verlet-list
};
typedef struct particle Particle;

extern gsl_rng *generator;
extern int dim;
extern int N;
extern double D;
extern double T;
extern long steps;
extern int rate;
extern double sigma;
extern long seed;
extern double dt;
extern double r_v;
extern double L;

#endif