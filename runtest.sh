#!/bin/bash

#files: wiki_sample.txt, test_big.txt, test_shortline.txt
fname='/home/cullen/cis520/LetsGitIt/proj4/wiki_dump.txt'
outname='log.txt'
nthreads=1000
searchtext='DATA'
psize=50
rm $outname

echo "OPEN MP" >> $outname
gcc -fopenmp -o 3way-openmp/openmp 3way-openmp/openmp_sol.c -lm
#./openmp.out $fname  $psize $nthreads | grep -c $searchtext >> $outname
./3way-openmp/openmp $fname $psize $nthreads | sort -g >> $outname

echo "MPI" >> $outname
mpicc -o 3way-mpi/mpiSol 3way-mpi/mpi_sol.c -lm 
./3way-mpi/mpiSol $fname $psize >> $outname
#mpirun -np $nthreads mpi_sol.c $fname $psize| grep $searchtext >> $outname

echo "PTHREADS" >> $outname
gcc -pthread -o 3way-pthread/pthreadrun 3way-pthread/pthread_sol.c -lm 
./3way-pthread/pthreadrun $fname $psize >> $outname
#mpirun -np $nthreads mpi_sol.c $fname $psize| grep $searchtext >> $outname

echo "Output: $outname"
