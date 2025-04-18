#!/bin/bash

# Slurm job options (name, compute nodes, job time)
#SBATCH --job-name=roofline
#SBATCH --time=0:20:0
#SBATCH --exclusive
#SBATCH --nodes=1
#SBATCH --tasks-per-node=36
#SBATCH --cpus-per-task=1

# Replace [budget code] below with your budget code (e.g. t01)
#SBATCH --account=m24ol-s2618173
# We use the "standard" partition as we are running on CPU nodes
#SBATCH --partition=standard
# We use the "standard" QoS as our runtime is less than 4 days
#SBATCH --qos=standard

#module load intel-tools-19
#module load intel-compilers-19

module load intel-20.4/compilers
module load intel-20.4/cmkl
module load intel-20.4/psxe		#icx compiler & advixe-gui (Intel advisor, rooflining, etc)
module load oneapi
module load compiler

#module load intel-19.5/compilers
#module load intel-19.5/vtune
#module load intel-19.5/pxse

# Change to the submission directory
cd $SLURM_SUBMIT_DIR

# Set the number of threads to 1
#   This prevents any threaded system libraries from automatically
#   using threading.
export OMP_NUM_THREADS=1
#mkdir -p orig_results
mkdir -p orig_results/roofline
#advixe-cl -collect survey -project-dir orig_results -- ./mult_orig 1024
#advixe-cl -collect tripcounts -flop -project-dir orig_results -- ./mult_orig 1024
advixe-cl -collect roofline -project-dir orig_results/roofline -- ./mult_orig 1024

mkdir -p opt_results
#advixe-cl -collect survey -project-dir opt_results -- ./mult_opt 1024
#advixe-cl -collect tripcounts -flop -project-dir opt_results -- ./mult_opt 1024
#advixe-cl -collect roofline -project-dir opt_results -- ./mult_opt 1024
