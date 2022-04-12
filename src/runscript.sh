#!/bin/bash

#SBATCH --nodes=2
#SBATCH --ntasks-per-node=12
#SBATCH --output=runscript.out
#SBATCH --time=00:10:00
#SBATCH --exclusive
#SBATCH --export=NONE

set +x
export I_MPI_OFI_LIBRARY_INTERNAL=0
module load intelmpi
module load libfabric-aws

set -x
ulimit -s unlimited
ulimit -l unlimited
ulimit -a

export FI_PROVIDER=efa
export I_MPI_DEBUG=4
export I_MPI_FABRICS=ofi
export I_MPI_HYDRA_BRANCH_COUNT=0
export I_MPI_OFI_PROVIDER=efa
export SLURM_EXPORT_ENV=ALL

mpiexec.hydra ./test

