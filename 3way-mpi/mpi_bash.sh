#!/bin/bash

mpi_init

fname='/mnt/c/Users/bgust/OneDrive/Documents/cis520/proj4/3way-mpi/wiki_dump.txt'
searchtext='DATA'
#problem='10000 100000 500000 1000000'
nthreads=$3

echo $1
#for i in $problem
#do
	echo "---PROBLEM SIZE: $2---"
	echo "---THREAD COUNT: $3---"
	for ((j = 0; j < 10; j++))
	do
		mpirun -np $nthreads lcs_mpi $fname $2| grep $searchtext 
	done
#done
