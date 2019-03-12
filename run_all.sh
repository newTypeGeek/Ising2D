#!/bin/bash

# Square lattice length
L=50

# Nearest neighbour coupling
J=1

# Temperature (min, max, and step)
T_min=0.50
T_max=3.00
T_step=0.01

# Number of iteration
n_tot=2010000000

# Step to begin sampling
n_start=2000000000

# Sampling interval
n_inter=10000

# Output file path
path1='result/data.txt'


# Loop over the temperature range [0.5, 3]
# with step = 0.01
for T in $(seq 0.50 0.01 3.00)
do 
	./ising2D_simulation $L $J $T $n_tot $n_start $n_inter $path1
done


