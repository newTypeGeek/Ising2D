/*
 * 2D Ising Model Simulation using Metropolis Hasting Algorithm
 * The Hamiltonian H is 
 *   H = -J \sum_{<i, j>} s_{i} s_{j}
 *   J is the coupling 
 *   <i,j> means sum over neareast neighbour
 *   Assume the lattice is a square lattice
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/input_check.h"
#include "../header/ising.h"




int main(int argc, char **argv){

	// Initialize random seed
	srand(time(NULL));


	if ( argc != 8 ){
		printf("2D Ising Model Metropolis Hastings Simulation\n");
		printf("Compute 4 quantites:\n");
		printf("  1. Total energy per spin\n");
		printf("  2. Total magnetization per spin\n");
		printf("  3. Heat capacity per spin\n");
		printf("  4. Magnetic susceptibility per spin\n");
		printf("---------------------------------------------\n");

		// Check if there are enough arguments input
		printf("Require 7 user input arguments only\n");
		printf("1. Square lattice length (positive integer)\n");
		printf("2. Nearest negihbour coupling (floating point)\n");
		printf("3. Temperature (positive floating point)\n");
		printf("4. Number of iteration (positive integer) \n");
		printf("5. Step to begin sampling (positive integer) \n");
		printf("6. Sampling interval (positive integer) \n");
		printf("7. File path to append result\n");
		return -1;
	}
	else {
		// Check if the input type is correct
		int is_ok = check_input_type(argv);
		if ( is_ok == 0 ){
			return -1;
		}
	}


	// Length of square lattice
	unsigned int L = atoi(argv[1]);

	// Coupling strength
	double J = atof(argv[2]);

	// Temperature
	double T = atof(argv[3]);

	// Number of iteration
	unsigned int iter_num = atoi(argv[4]);

	// Iteration step that to start sampling
	unsigned int start_sample = atoi(argv[5]);

	// Iteration interval of sampling
	unsigned int sample_interval = atoi(argv[6]);


	// Number of sample
	int sample_num = (iter_num - start_sample)/sample_interval;
	if ( sample_num <= 0 ){
		printf("No sampling!\n");
		return -1;
	}

	// Path to store result
	char *file_result = argv[7];
	
	

	printf("Square lattice length             L = %d\n", L);
	printf("Total number of spin        N = LxL = %d\n", L*L);
	printf("Nearest neighbour coupling        J = %.10f\n", J);
	printf("Temperature                       T = %.10f\n", T);
	printf("Number of iteration                 = %d\n", iter_num);
	printf("Step to begin sampling              = %d\n", start_sample);
	printf("Sampling interval                   = %d\n", sample_interval);
	printf("Number of sample                    = %d\n", sample_num);


	// Start Metropolis Hasting Simulation
	// It computes 4 quantities:
	// 1. Total energy per spin
	// 2. Total magnetization per spin
	// 3. Heat capacity per spin
	// 4. Magnetic susceptibility per spin
	metropolis_hastings(L, J, T, iter_num, start_sample, sample_interval, file_result);


	return 0;
}

