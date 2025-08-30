#include "WCABD.h"
#include "init.h"
#include "bd.h"
#include "printdata.h"
#include "distance.h"
#include "verletlist.h"
#include "inputdata.h"
#include "printdisplay.h"
#include "calc.h"
#include "force.h"

// ----------------------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------------------    

gsl_rng *generator = NULL;                                  // Random number generator
int dim = DIM;
int N = NP;
double D = DDD;
double T = TEMP;
long steps = STEPS;
int rate = RATE;
double sigma = SIGMA;
long seed = SEED;
double dt = DT;
double r_v = RV;
double L = LL;

int main(int argc, char *argv[]) {
	
	// For the calculation of the total simulation time. 
    time_t start;
    time(&start);
	
	PrintWelcome();
	
	// The program only runs with "inputfile" in the same folder. 
    // A new inputfile can be generated with "./NpT_SC.exe Setup"
    if (argc == 2 && !strcmp(argv[1], "Setup")) {

        // Generates an example input file which can be customized. 
        PrintInputfile();     // See inputdata.c

        time_t now;
        time(&now);

        // Total simulation time.
        long simTime = now - start;
        printf("Duration of the simulation: %ld s\n", simTime);

        return 0;
    }
	
	ReadInput();
	PrintInput();
	CheckForConflict();	
	
	Particle P[N];
	
	// See GSL documentation for more info regarding the generator.
    // GLS has to be linked to get random numbers!
    generator = gsl_rng_alloc(gsl_rng_mt19937);
    printf("Random number generator: mt19937\n");
    gsl_rng_set(generator, seed);
	
	InitRandom(P);
	
	FILE *position_file_ovito = NULL;
    position_file_ovito = fopen("Position_For_Ovito.xyz", "w");
	
	GenerateVerletLists(P);
	long counter_verlet = 1;
	
	int resolution, min_rate, n_min;
	long n_max, t_samp;
    double a, e;
    InitParametersCalcFACF(&resolution, &min_rate, &a, &e, &n_min, &n_max, &t_samp, steps);

	long *lengthF;
    long *rateF;
    long **sample;
    InitiSampleArraysCalcFACF(n_max, n_min, a, e, &lengthF, &rateF, &sample);
	
	unsigned long long *counter_FACF;
    double *facf;
	double *nfcf;
    double ****f0;
	double ****n0;
    InitStorageArraysFACF(n_max, rateF, N, dim, &counter_FACF, &facf, &nfcf, &f0, &n0);	
	
	for (long step = 0; step < steps; step++) {
		
		BrownianMotion(P);
		
		CalcForce(P);			
		
		if(CheckVerlet(P)) {
			GenerateVerletLists(P);
			counter_verlet++;
		}
		
		if(step > EQ) {
			CalcFACF(n_max, sample, lengthF, rateF, facf, nfcf, f0, n0, counter_FACF, P, &t_samp);
		}
				
		if ((step + 1) % (long)rate == 0) {
			PrintOvito(position_file_ovito, P, step);
		}
	}
	
	FILE *facf_file = NULL;
    facf_file = fopen("facf.dat", "w");
	PrintFACF(facf_file, n_max, lengthF, facf, nfcf, counter_FACF);
	fclose(facf_file);
	
	printf("Verlet-lists were updated %ld times.\n", counter_verlet);
	
	gsl_rng_free(generator);
	fclose(position_file_ovito);
	FreeVerLists(P);
	FreeMemoryFACF(n_max, sample, lengthF, rateF, facf, nfcf, f0, n0);
	
	// Obtains the calendar time at the end of the simulation.
    time_t now;
    time(&now);

	// Calculating the duration of the simulation
    long simTime = now - start;
    printf("Duration of the simulation: %ld s\n", simTime);
	
    // End of simulation
    return 0;
}