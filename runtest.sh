#!/bin/bash

#files: wiki_sample.txt, test_big.txt, test_shortline.txt
fname='/home/cullen/cis520/LetsGitIt/proj4/wiki_dump.txt'
outname='log.txt'
nthreads=1000
searchtext='DATA'
psize=50
rm $outname

echo "--------OPEN MP--------" >> $outname
gcc -fopenmp -o openmp.out openmp_sol.c -lm
#./openmp.out $fname  $psize $nthreads | grep -c $searchtext >> $outname
./openmp.out $fname  $psize $nthreads >> $outname

echo "----------MPI----------" >> $outname
mpicc -o mpiSol mpi_sol.c -lm
./mpiSol $fname  $psize $nthreads >> $outname
#mpirun -np $nthreads mpi_sol.c $fname $psize| grep $searchtext >> $outname

echo "COMPLETE: See $outname"
