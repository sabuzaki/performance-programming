#!/bin/sh

#SBATCH --nodes=1
#SBATCH --time=3:00:0
#SBATCH --partition=standard
#SBATCH --qos=standard
#SBATCH --exclusive
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=1

module load oneapi
module load compiler

# Switch to current working directory
cd C

# Run the parallel program
./MD



