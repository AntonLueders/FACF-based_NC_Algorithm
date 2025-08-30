# Introduction

The noise-cancellation (NC) algorithm recently introduced by Mandal et al. [Mandal et al. PRL 2019] is an effective method to obtain high-accuracy velocity-correlation data from Brownian dynamics (BD) simulations, especially in the long-time regime. Its core concept is to decompose particle displacements into the contributions of the Brownian motion and the deterministic forces. Then, terms arising from the cross-correlation of these two contributions are neglected while evaluating the velocity autocorrelation function (VACF). As discussed in  

[1] *Connection between the noise-cancellation algorithm for Brownian particles and the force autocorrelation function and its applicability to arbitrary overdamped systems* by Anton Lüders, Suvendu Mandal, and Thomas Franosch,

This strategy is equivalent to approximating the VACF with the force autocorrelation function (FACF) in thermal equilibrium. For nonequilibrium systems, the NC algorithm must be adjusted, as the VACF cannot be represented by the FACF alone. 

This repository contains the software that is used to perform the simulations presented in [1].

All information and methods employed in the code of this repository are described in detail in the main text and appendix of [1]. While the given code can be used to repeat the corresponding simulations, we strongly encourage a full independent reproduction using the information in said corresponding manuscript.  

# Table of content:
 - [Contents of the particular folders](#Contents)
 - [Requirements](#Requirements)
 - [How to build the code](#Build)
 - [How to use the code](#Use)
 - [How to interprete the generated data](#Data)
 - [Disclaimer](#Disclaimer)
 - [Cite this software](#Cite)

 <a id="Contents"></a>
# Contents of the particular folders

The repository contains multiple folders, each containing the software for one of the example systems studied in [1]. The folder *WCA* contains the code for the soft-sphere simulations. The folder *HS* contains all files necessary for the hard-sphere simulations based on the "potential-free" BD algorithm of Meyes and Melrose [Heyes et al. J. Non-Newton. Fluid Mech. 1993]. In *Driven*, an adjusted version of the hard-sphere program can be found, where the particles are driven in the positive x-direction. Finally, *ABP* contains the code for the simulations corresponding to an active Brownian particle (ABP) in a harmonic potential.
 
 <a id="Requirements"></a>
# Requirements

The program is written in *C* (C99 standard). The data presented in [1] was obtained by a binary build with gcc 13.3.0. Hence, the functionality was checked for this version of the GNU compiler. 

To compile the code in this repository, the library GSL must be linked (which is used for random number generation). The binary used for the simulations corresponding to [1] was built with version GSL 2.8.

 <a id="Build"></a>
# How to build the code

The source files of the different programs can be found in the corresponding folders in this repository. Example makefiles are given in said folders as well. As usual, it can be used to compile the program by typing 

``
make
``

in the console while being in the folder that contains the source files. 
 
 <a id="Use"></a>
# How to use the code

To run the simulation software, an input file (called *inputfile*) with the simulation parameters must be in the same folder as the binary. Then, the binary can be executed as usual.

The input file for the equilibrium setups (soft- and hard-sphere systems) must look like the following example:

```
dim       3
N       1000
T       1.000000
steps     2000000000
rate     2000000
sigma   1.000000
seed     20
dt     0.0002
r_v     2.5
L       37.411000
```
Here, The particular lines of such an input file are summarized in the following list:

- *dim:* Dimension of the system
- *N:* Number of particles
- *T:* Thermal energy kT. Should be fixed to 1.0 for standard BD simulations
- *steps:* Number of simulation steps
- *rate:* The positions of the particles are saved in an external file every "rate" simulation steps
- *sigma:* Particle diameter. Should be fixed to 1.0
- *seed:* Seed for the random number generator
- *dt:* Length of a simulation step in units of the Brownian time
- *r_v:* Radius for the Verlet lists
- *L:* Box length of the simulation box

 <a id="Data"></a>
# How to interprete the generated data

All simulation programs in this repository output two files at the end of a simulation run:

- *Position_For_Ovito.xyz:* This file stores the particle positions. Every "rate" simulation steps, the center coordinates are stored in this file.
- *facf.dat:* This file contains the correlation functions calculated by the particular simulation software. All correlation functions are calculated using the algorithm introduced in [Siems et al. J. Phys. Conf. Ser. 2018]. The first column is always the times at which the correlations are calculated. The other columns of this file are the FACF and the VACF for the soft-sphere simulations, the FACF and the force-noise correlations for the hard-sphere simulations, the interaction FACF, the total FACF, and the total force-noise correlations for the simulations with the driven particles, and the FACF and the noise-force correlations for the ABP simulations.

To visualize the dynamics of the system, it is suggested to use external software that can interpret the xyz position files. For this, *VMD* [Humphrey et al. J. Mol. Graph. 1996] or *OVITO* [https://www.ovito.org/] can be used.

 <a id="Disclaimer"></a>
# Disclaimer

Note that the presented code is **not** an ongoing software project with active support. Instead, it is part of the appendix of [1] and reflects the state of the software used to obtain the corresponding numerical results. For any questions regarding [1] and the corresponding data, please contact the corresponding authors.

 <a id="Cite"></a>
# Cite this software

If you use this simulation software or parts of it, please cite

[1] *Connection between the noise-cancellation algorithm for Brownian particles and the force autocorrelation function and its applicability to arbitrary overdamped systems* by Anton Lüders, Suvendu Mandal, and Thomas Franosch.
