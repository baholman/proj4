#!/bin/bash

sbatch --constraint=elves --time=5:00:00 --mem-per-cpu=5G --nodes=1 --cpus-per-task=16 mpi_shell_script.sh