#include "printdisplay.h"

// ----------------------------------------------------------------------------------------

// Welcome screen with the information of the program. (Is printed to the console).
void PrintWelcome() {

    printf("\n");

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
           "++++"
           "+++++++\n");
    printf("+                                                                  "
           "    "
           "      +\n");
    printf("+             Simple Soft Sphere Brownian Dynamics                 "
           "    "
           "      +\n");
    printf("+             ABP version                                          "
           "    "
           "      +\n");
    printf("+                                                                  "
           "    "
           "      +\n");
    printf("+             Author:   Anton Lueders                              "
           "    "
           "      +\n");
    printf("+             Date:     07.04.2025                                 "
           "    "
           "      +\n");
    printf("+                                                                  "
           "    "
           "      +\n");
    printf("+             AG Franosch                                          "
           "    "
           "      +\n");
    printf("+             BioNano-Physics                                      "
           "    "
           "      +\n");
    printf("+             Univesity of Innsbruck                               "
           "    "
           "      +\n");
    printf("+                                                                  "
           "    "
           "      +\n");
    printf("+             Last edited: 28.01.2026                              "
           "    "
           "      +\n");
    printf("+                                                                  "
           "    "
           "      +\n");
    printf("+             V1.0.2                                               "
           "          +\n");
    printf("+                                                                  "
           "    "
           "      +\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
           "++++"
           "+++++++\n");

    printf("\n");
}

// ----------------------------------------------------------------------------------------

// Prints the input data (global variables) to the console.
void PrintInput() {

    printf("The simulation was started using the following input:\n");

    printf("\n");
	
	printf("dim\t%d\n", dim);
	printf("N\t%d\n", N);
    printf("D\t%1.6f\n", D);
	printf("T\t%1.6f\n", T);
	printf("steps\t%ld\n", steps);
	printf("rate\t%d\n", rate);
	printf("sigma\t%1.6f\n", sigma);
	printf("dt\t%1.6f\n", dt);
	printf("r_v\t%1.6f\n", r_v);
	printf("L\t%1.6f\n", L);
	printf("force\t%1.6f\n", force);
}

// ----------------------------------------------------------------------------------------

