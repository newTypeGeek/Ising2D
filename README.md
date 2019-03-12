# Ising2D
Using Metropolis Hasting algorithm to simulate a 2D Ising model in a square lattice.

In statistical mechanics, we would like to compute macroscopic quantities (e.g. heat capacity) from the Hamiltonian. Analytic calculation using pen and paper involves a computation of expectation value (i.e. mean value). Unfortunately, analytic / closed-form solution exists for some systems only. To deal with realistic, complex systems, one must seek for numerical solutions. <br>

One of the simplest methods is to generate samples using **Monte Carlo** simulation.
The trick here is to make use of Markov Chain, hence the name **Monte-Carlo Markov Chain (MCMC)** method, to generate the desired samples.
The key idea is to construct a transition probability of the Markov Chain is stationary and it would converge to the desired probability distribution (i.e. Boltzmann distribution in this case).
The algorithm that we used here is known as **Metropolis Hasting algorithm**. 

In this project, the Hamiltonian is a standard 2D Ising model in a finite square lattce with nearest neighbour coupling. Each spin takes a value of -1 or +1. Periodic boundary condition is used.


# Getting Started

Clone this project to your working directory <br>
`$ git clone https://github.com/newTypeGeek/Ising2D.git`

Compile the source code to executable<br>
`$ gcc -O3 source/*.c -o ising2D_simulation`

You can also run the bash script<br>
`$ chmod +x compile.sh`<br>
`$ ./compile.sh`

# Simulate a single case
User is required to input 7 arguments as shown below
```
$ ./ising2D_simulation`
2D Ising Model Metropolis Hastings Simulation
Compute 4 quantites:
  1. Total energy per spin
  2. Total magnetization per spin
  3. Heat capacity per spin
  4. Magnetic susceptibility per spin
---------------------------------------------
Require 7 user input arguments only
1. Square lattice length (positive integer)
2. Nearest negihbour coupling (floating point)
3. Temperature (positive floating point)
4. Number of iteration (positive integer) 
5. Step to begin sampling (positive integer) 
6. Sampling interval (positive integer) 
7. File path to append result
```

For example, you could try the following.<br>
```
$ ./ising2D_simulation 50 1 2 2010000000 2000000000 10000 test.txt
   Square lattice length             L = 50
   Total number of spin        N = LxL = 2500
   Nearest neighbour coupling        J = 1.0000000000
   Temperature                       T = 2.0000000000
   Number of iteration                 = 2010000000
   Step to begin sampling              = 2000000000
   Sampling interval                   = 10000
   Number of sample                    = 1000
   E_per_spin = -1.7463344000
   M_per_spin = 0.9118320000
   C_per_spin = 0.6504773104
   X_per_spin = 0.3451087200
   Time elapsed (in sec) = 63.1119290000
```
The result is then appended to `test.txt` as shown below.

* Column 1:  Temperature <br>
* Column 2:  Nearest neighbour coupling <br>
* Column 3:  Total energy per spin <br>
* Column 4:  Total magnetization per spin <br>
* Column 5:  Heat capacity per spin <br>
* Column 6:  Magnetic susceptibility per spin <br>
* Column 7:  Time elapsed in seconds <br>
```
$ vim test.txt
2.0000000000, 1.0000000000, -1.7463344000, 0.9118320000, 0.6504773104, 0.3451087200, 63.1119290000
~  
```

# Simulate with different temperatures
You can generate the results with different temperature using `run_all.sh`.<br>
In this case, we loop over a temperature from 0.50 to 3.00 with an increment step of 0.01
```
$ chmod +x run_all.sh
$ ./run_all.sh
```
All the results are appended to `result/data.txt`. <br>
Plots are included in `result` directory and they are shown below. <br>
The take home message for this exercise is that, near critical temperature (red dashed line), the result is bad.
When the system is near critical point, the correlation between different samples are very large. Note that the sampling interval in this `run_all.sh` is fixed for all temperature, and we do not consider **Importance of Sampling** in details.

<img src="https://github.com/newTypeGeek/Ising2D/blob/master/result/Ene_vs_T.png"
alt="Energy per spin versus temperature" width="360">
<img src="https://github.com/newTypeGeek/Ising2D/blob/master/result/Cap_vs_T.png" 
alt="Heat capacity per spin versus temperature" width="360">
<img src="https://github.com/newTypeGeek/Ising2D/blob/master/result/Mag_vs_T.png"
alt="Absolute magnetization per spin versus temperature" width="360">
<img src="https://github.com/newTypeGeek/Ising2D/blob/master/result/Sus_vs_T.png"
alt="Magnetic susceptibility per spin versus temperature" width="360">

