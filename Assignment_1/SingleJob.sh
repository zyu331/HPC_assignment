#!/bin/sh

#PBS -N HPC
#PBS -q coc-ice
#PBS -o output
#PBS -j oe
#PBS -l nodes=1:ppn=myN
#PBS -l walltime=1:00:00
#PBS -l mem=4gb
#PBS -S /bin/bash

cd $PBS_O_WORKDIR

module purge
module load gcc/4.9.0
module load mvapich2/2.2

mpicxx prog1.cpp -o prog1
mpirun -np myN ./prog1 myN mySeed > out
