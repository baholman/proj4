#!/bin/bash

fname='~/cis520/LetsGitIt/proj4/3way-mpi/wiki_dump.txt'
searchtext='DATA'
#problem='10000 100000 500000 1000000'
nthreads=$3
sudo modprobe OpenMPI
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
