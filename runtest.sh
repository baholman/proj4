#!/bin/bash

#files: wiki_sample.txt, test_big.txt, test_shortline.txt
fname='/mnt/c/Users/bgust/OneDrive/Documents/cis520/proj4/wiki_dump.txt'
outname='log.txt'
nthreads=1000
searchtext='DATA'
psize=50
rm $outname

echo "\nOPEN MP" >> $outname
gcc -fopenmp -o openmp openmp_sol.c -lm
#./openmp.out $fname  $psize $nthreads | grep -c $searchtext >> $outname
./openmp $fname  $psize $nthreads | sort -g >> $outname

echo "\nMPI" >> $outname
mpicc -o mpiSol mpi_sol.c -lm 
./mpiSol $fname  $psize >> $outname
#mpirun -np $nthreads mpi_sol.c $fname $psize| grep $searchtext >> $outname

echo "\nPTHREADS" >> $outname
gcc -pthread -o pthreadrun pthread_sol.c -lm 
./pthreadrun $fname  $psize $nthreads >> $outname
#mpirun -np $nthreads mpi_sol.c $fname $psize| grep $searchtext >> $outname

echo "Output: $outname"
