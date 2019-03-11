# Ising2D
Using Metropolis Hasting algorithm to simulate a 2D Ising model in a square lattice

# Getting Started

Clone this project to your working directory <br>
`$ git clone https://github.com/newTypeGeek/Ising2D.git`

Compile the source code to executable<br>
`$ gcc -O3 source/*.c -o ising2D_simulation`

You can also run the bash script<br>
`$ chmod +x compile.sh`<br>
`$ ./compile.sh`

# How to Run
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

For example
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
The result is appended to test.txt.

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

You can generate the results with different temperature using `run_all.sh`.<br>
```
$ chmod +x run_all.sh
$ ./run_all.sh
```
All the results are appended to `result/data.txt`

# Plot the results
The python script in `result/plot_result.py` plots the physical quantities versus temperature.
I have included some figures as a reference

## Required modulues 
NumPy
Matplotlib
```
$ cd result
$ python3 result/plot_result.py
```
