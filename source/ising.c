#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../header/ising.h"


// Evaluate the correct lattice point i of a lattice with
// length L when the periodic boundary condition taken into account
int bc(int i, int L){
	int i_new = 0;

	if ( i > L - 1 ){
		i_new = i - L;
	}
	else if ( i < 0 ){
		i_new = i + L;
	}
	else {
		i_new = i;
	}

	return i_new;
}


// Compute the nearest negihbour interaction energy of the selected spin at
// site (row, col) given the input spin configuration -- spins, of size L x L
// with uniform coupling J
double centre_energy(int centre, int upper, int lower, int left, int right, double J){
	return -J*centre*(upper + lower + left + right);
}


// Compute the total magnetization of the input 
// spin configuration -- spins, of size L x L 
double total_magnetization(int *spins, unsigned int L){
	double mag_tot = 0;
	for(int i = 0; i < L; i++){
		for(int j = 0; j < L; j++){
			mag_tot = mag_tot + (double)spins[i*L+j];
		}
	}
	return mag_tot;
}


// Compute the total energy of the input 
// spin configuration -- spins, of size L x L with a uniform coupling J
double total_energy(int *spins, unsigned int L, double J){
	
	double eng_tot = 0.0;	
	int centre = 0;
	int upper = 0;
	int lower = 0;
	int left = 0;
	int right = 0;

	for(int i = 0; i < L; i++){
		for(int j = 0; j < L; j++){
			centre = spins[i*L+j];
			upper = spins[bc(i-1,L)*L + j];
			lower = spins[bc(i+1,L)*L + j];
			left = spins[i*L + bc(j-1,L)];
			right = spins[i*L + bc(j+1,L)];

			eng_tot = eng_tot + centre_energy(centre, upper, lower, left, right, J);
		}
	}

	return 0.5*eng_tot;	
}


// Randomly select a spin and attempt to flip the spin state from the spin configuration 
// -- spins of a square lattice with length L and uniform coupling J at temperature T.
// With the energy difference dE of the two spin configurations, the new configuration 
// is accepted according to the acceptance ratio min[1, exp(-dE/T)
void spin_flip(int *spins, unsigned int L, double J, double T, double *dE, double *dM){
	
	// Randomly select a spin to flip
	int i = rand() % L;
	int j = rand() % L;
	int centre = spins[i*L+j];
	int upper = spins[bc(i-1,L)*L + j];
	int lower = spins[bc(i+1,L)*L + j];
	int left = spins[i*L + bc(j-1,L)];
	int right = spins[i*L + bc(j+1,L)];

	// Compute the energy difference
	*dE = centre_energy(-1*centre, upper, lower, left, right, J) - centre_energy(centre, upper, lower, left, right, J);
	
	*dM = -2*centre;


	// Accept the new configuration according to the
	// acceptance ratio : min[1, exp(-dE/T)]
	if( *dE < 0 ){
		spins[i*L+j] = -1*spins[i*L+j];
	}
	else{
		if( rand()/(double)RAND_MAX <= exp(-*dE/T) ){
			spins[i*L+j] = -1*spins[i*L+j];
		}
		else {
			*dE = 0;
			*dM = 0;
		}
	}


}


// Initialize the spin configuration -- spins of a square lattice
// with length L. Each spin takes a value of either 1 or -1.
void initialization(int *spins, unsigned int L){
	for(int i = 0; i < L; i++){
		for(int j = 0; j < L; j++){
			spins[i*L+j] = rand() % 2;

			if( spins[i*L+j] == 0 ){
				spins[i*L+j] = -1;
			}
		}
	}
}



// Metropolis Hastings algorithm is one of the Markov Chain Monte Carlo (MCMC) methods. It is used
// to sample random variables from a highly complex probability distribution.
//
// By constructing a Markov Chain with sufficiently large number of iteration, 
// the random variables would converge to the desired equilibrium distribution.
//
// In our case the random variable is spin configuration -- spins,
// and the equilibrium distribution is the Boltzmann distribution
//
// Our Markov Chain is constructed inside the spin_flip function.
// Moreover, we compute several quantities of interest
// 1. Total energy per spin: 
//    < E > / N
// 2. Total magnetization per spin: 
//    < M > / N
// 3. Heat capacity per spin: 
//    C / N  = (1/N) (1/kT^2) ( < E^2 > - < E >^2 )
// 4. Magnetic susceptibility per spin: 
//    X / N = (1/N) (1/kT) ( < M^2 > - < M >^2 )
//
void metropolis_hastings(unsigned int L, double J, double T, 
		unsigned int iter_num, unsigned int start_sample, 
		unsigned int sample_interval, char *file_result){

	// Initialize spin configuration and compute
	// the total energy and total magnetization
	int *spins = calloc(L*L, sizeof(int));
	initialization(spins, L);
	double E_tot = total_energy(spins, L, J);
	double M_tot = total_magnetization(spins, L);
	int N = L*L;


	// Sampled energy and magnetization
	// Label with 1: total sum
	// Label with 2: squared sum
	double E1 = 0;
	double E2 = 0;
	double M1 = 0;
	double M2 = 0;

	// Total number of sample
	int sample_num = 0;


	// dE, dM are the change in total energy,
	// and total magnetization for each iteration
	double *dE = calloc(1, sizeof(double));
	double *dM = calloc(1, sizeof(double));

	
	// Count the simulation time
	clock_t start_time = clock();
	for(int i = 0; i < iter_num; i++){

		// Perform spin flip and accept new configuration
		// according to acceptance ratio min[1, exp(-dE/T)]
		spin_flip(spins, L, J, T, dE, dM);


		// Update the total energy and total magnetization
		E_tot = E_tot + *dE;
		M_tot = M_tot + *dM;


		// Take sample if the conditions are fulfilled
		if( i >= start_sample && i % sample_interval == 0 ){
			E1 = E1 + E_tot;
			E2 = E2 + E_tot*E_tot;

			M1 = M1 + M_tot;
			M2 = M2 + M_tot*M_tot;

			sample_num++;
		}
	}	
	free(dE);
	free(dM);


	clock_t end_time = clock();
	double time_elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;


	// Total energy per spin
	double E_per_spin = E1/(sample_num*N);

	// Total magnetization per spin
	double M_per_spin = M1/(sample_num*N);

	// Heat capacity per spin
	double C_per_spin = ( E2/sample_num - (E1*E1)/(sample_num*sample_num) ) / (T*T*N);

	// Magnetic susceptibility per spin
	double X_per_spin = ( M2/sample_num - (M1*M1)/(sample_num*sample_num) ) / (T*N);

	
        printf("E_per_spin = %.10f\n", E_per_spin);
        printf("M_per_spin = %.10f\n", M_per_spin);
        printf("C_per_spin = %.10f\n", C_per_spin);
        printf("X_per_spin = %.10f\n", X_per_spin);
        printf("Time elapsed (in sec) = %.10f\n\n", time_elapsed);



	// Append the result to the file_result
	FILE *result_file = fopen(file_result, "a+");
	fprintf(result_file, "%.10f, %.10f, %.10f, %.10f, %.10f, %.10f, %.10f\n",
			T, J,
			E_per_spin, M_per_spin, 
			C_per_spin, X_per_spin,
                        time_elapsed
               );
	fclose(result_file);

	free(spins);
}



