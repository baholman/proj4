#!/bin/bash

#files: wiki_sample.txt, test_big.txt, test_shortline.txt
fname='/mnt/c/Users/bgust/OneDrive/Documents/cis520/proj4/wiki_dump.txt'
outname='log.txt'
nthreads=12
searchtext='DATA'
psize=5
rm $outname

echo "--------OPEN MP--------" >> $outname
gcc -fopenmp -o openmp.out openmp_sol.c -lm
#./openmp.out $fname  $psize $nthreads | grep -c $searchtext >> $outname
./openmp.out $fname  $psize $nthreads >> $outname

echo "----------MPI----------" >> $outname
gcc -o mpiSol mpi_sol.c -lm
./mpiSol $fname  $psize $nthreads >> $outname
#mpirun -np $nthreads mpi_sol.c $fname $psize| grep $searchtext >> $outname

echo "COMPLETE: See $outname"
