#!/bin/bash
#SBATCH --chdir=/fs/fsx/tmp/limits/
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=12
#SBATCH --output=runscript.out
#SBATCH --time=00:10:00
#SBATCH --exclusive
#SBATCH --export=NONE

set -x

ulimit -s unlimited
ulimit -l unlimited
ulimit -a

set +x
export I_MPI_OFI_LIBRARY_INTERNAL=0
module use /fs/fsx/sw/spack/share/spack/modules/linux-amzn2-zen
module use /fs/fsx/sw/spack/share/spack/modules/linux-amzn2-zen2
module load intel-oneapi-compilers-2021.4.0-gcc-7.3.1-sbo62ze
module load intel-oneapi-mpi-2021.4.0-intel-2021.4.0-ncckbpa
module load libfabric-aws/1.13.2amzn1.0

export FI_PROVIDER=efa
export I_MPI_DEBUG=4
export I_MPI_FABRICS=ofi
export I_MPI_HYDRA_BRANCH_COUNT=0
export I_MPI_OFI_PROVIDER=efa
export SLURM_EXPORT_ENV=ALL

mpiexec.hydra -np $SLURM_NTASKS --ppn $SLURM_NTASKS_PER_NODE ./test

