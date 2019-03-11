// Evaluate the correct lattice point i of a lattice with
// length L when the periodic boundary condition taken into account
int bc(int i, int L);

// Compute the nearest negihbour interaction energy of the selected spin at
// site (row, col) given the input spin configuration -- spins, of size L x L
// with uniform coupling J
double centre_energy(int centre, int upper, int lower, int left, int right, double J);


// Compute the total magnetization of the input 
// spin configuration -- spins, of size L x L 
double total_magnetization(int *spins, unsigned int L);

// Compute the total energy of the input 
// spin configuration -- spins, of size L x L with a uniform coupling J
double total_energy(int *spins, unsigned int L, double J);
	
	
// Randomly select a spin and attempt to flip the spin state from the spin configuration 
// -- spins of a square lattice with length L and uniform coupling J at temperature T.
// With the energy difference dE of the two spin configurations, the new configuration 
// is accepted according to the acceptance ratio min[1, exp(-dE/T)
void spin_flip(int *spins, unsigned int L, double J, double T, double *dE, double *dM);



// Initialize the spin configuration -- spins of a square lattice
// with length L. Each spin takes a value of either 1 or -1.
void initialization(int *spins, unsigned int L);






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
		unsigned int sample_interval, char *file_result);
