# poisson_using_petsc

Try solving the poisson equation using the finite element method using petsc.

## Prerequisites
- Linux OS
- PETSc (https://petsc.org/) 
  - 3.20.6 in this work

### build PETSc
In the case of using bash and git:
```bash
git clone -b release https://gitlab.com/petsc/petsc.git petsc_nomkl
cd petsc_nomkl
unset PETSC_DIR
./configure \
  --prefix=${HOME}/local/petsccomplex_nomkl \
  --with-petsc-arch=linux64complexnomkl \
  --with-scalar-type=complex \
  --with-openmp=1 \
  --with-avx512-kernels=0 \
  --download-triangle \
  --download-tetgen \
  --download-mumps \
  --download-scalapack \
  2>&1 | tee configurelog.txt
make -j12 PETSC_DIR=`pwd` PETSC_ARCH=linux64complexnomkl all 2>&1 | tee makelog.txt
make PETSC_DIR=`pwd` PETSC_ARCH=linux64complexnomkl install
```
then,
```bash
export PETSC_DIR=${HOME}/local/petsccomplex_nomkl
```

### build exercises
```bash
cd exercises
make
```

