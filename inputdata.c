#include "inputdata.h"

// ----------------------------------------------------------------------------------------

// Prints inputfile if "Setup" is used.
void PrintInputfile() {

    printf("Write intput file using the default values. Please wait...\n");

    printf("\n");

    FILE *file = fopen("inputfile", "w");
	fprintf(file, "dim\t%d", dim);
	fprintf(file, "N\t%d\n", N);
	fprintf(file, "T\t%1.6f\n", T);
	fprintf(file, "steps\t%ld\n", steps);
	fprintf(file, "rate\t%d\n", rate);
	fprintf(file, "sigma\t%1.6f\n", sigma);
	fprintf(file, "seed\t%ld\n", seed);
	fprintf(file, "dt\t%1.6f\n", dt);
	fprintf(file, "r_v\t%1.6f\n", r_v);
	fprintf(file, "L\t%1.6f\n", L);

    fclose(file);
}

// ----------------------------------------------------------------------------------------

// Reads inputfile. First, the parameters are stored in the "temp" variables are generated. 
// If reading the input was successfully, the global variables are set to the temp values.
void ReadInput() {

    // If there is no inputfile, an error occures.
    FILE *input = fopen("inputfile", "r");
    if (input == NULL) {
        printf("ERROR: No input found. Use Setup option.\n");

        printf("\n");

        exit(1);
    }
	
	// Temp variables
    char dummy[40] = " ";
    char temp[40] = " ";
	int dim_temp = dim;
	int N_temp = N;
	double T_temp = T;
	long steps_temp = steps;
	int rate_temp = rate;
	double sigma_temp = sigma;
	long seed_temp = (long)seed;
	double dt_temp = dt;
	double r_v_temp = r_v;
	double L_temp = L;

	
	// Reading the inputfile
	if (fscanf(input, "%s\t%d%[^\n]\n", temp, &dim_temp, dummy) == 2) {
        dim = dim_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (dim)\n");
        exit(1);
    }
    if (fscanf(input, "%s\t%d%[^\n]\n", temp, &N_temp, dummy) == 2) {
        N = N_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (N)\n");
        exit(1);
    }
	if (fscanf(input, "%s\t%lf%[^\n]\n", temp, &T_temp, dummy) == 2) {
        T = T_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (T)\n");
        exit(1);
    }
	if (fscanf(input, "%s\t%ld%[^\n]\n", temp, &steps_temp, dummy) == 2) {
        steps = steps_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (steps)\n");
        exit(1);
    }
	if (fscanf(input, "%s\t%d%[^\n]\n", temp, &rate_temp, dummy) == 2) {
        rate = rate_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (rate)\n");
        exit(1);
    }
	if (fscanf(input, "%s\t%lf%[^\n]\n", temp, &sigma_temp, dummy) == 2) {
        sigma = sigma_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (sigma)\n");
        exit(1);
    }
    if (fscanf(input, "%s\t%ld%[^\n]\n", temp, &seed_temp, dummy) == 2) {
        seed = (long)seed_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (seed)\n");
        exit(1);
    }	
	if (fscanf(input, "%s\t%lf%[^\n]\n", temp, &dt_temp, dummy) == 2) {
        dt = dt_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (dt)\n");
        exit(1);
    }
	if (fscanf(input, "%s\t%lf%[^\n]\n", temp, &r_v_temp, dummy) == 2) {
        r_v = r_v_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (r_v)\n");
        exit(1);
    }
	if (fscanf(input, "%s\t%lf%[^\n]\n", temp, &L_temp, dummy) == 2) {
        L = L_temp;
    } else {
        printf("ERROR: Check input or use Setup option. (L)\n");
        exit(1);
    }	
	
	fclose(input);
}

// Checks for conflicting input
void CheckForConflict() {
    
	if (N < 1) {
        printf("ERROR: Use at least 1 particle.\n");
        exit(1);
    }
    
    if (T < 0.) {
        printf("ERROR: Negative temperature is not defined.\n");
        exit(1);        
    }
    
    if (rate > steps) {
        printf("ERROR: Rate must be larger than steps.\n");
        exit(1);    
    }
	
	if (dim < 0 || dim > 3) {
		printf("ERROR: Enter a valid dimension.\n");
        exit(1);  
	}
}
