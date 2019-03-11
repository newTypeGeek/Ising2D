#!/bin/bash

# Tc=2.269185

L=50
J=1
n_tot=2010000000
n_start=2000000000
n_inter=10000
path1='result/data.txt'

for T in $(seq 2.93 0.01 3.01);
do 
	./ising2D_simulation $L $J $T $n_tot $n_start $n_inter $path1
done


