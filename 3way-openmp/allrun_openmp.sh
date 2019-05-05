#!/bin/bash

sbatch --constraint=elves --time=5:00:00 --mem-per-cpu=5G --nodes=1 --cpus-per-task=16 openmp_shell_script.sh
sbatch --constraint=elves --time=5:00:00 --mem-per-cpu=5G --nodes=2 --cpus-per-task=16 openmp_shell_script.sh
sbatch --constraint=elves --time=5:00:00 --mem-per-cpu=5G --nodes=4 --cpus-per-task=16 openmp_shell_script.sh
sbatch --constraint=elves --time=5:00:00 --mem-per-cpu=5G --nodes=8 --cpus-per-task=16 openmp_shell_script.sh
sbatch --constraint=elves --time=5:00:00 --mem-per-cpu=5G --nodes=16 --cpus-per-task=16 openmp_shell_script.sh
