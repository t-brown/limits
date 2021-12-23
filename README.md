Limits
======

`limits` is a small library that allows a FORTRAN program query to `getrlimit()`.

Prerequisites
-------------
+  [Make](https://www.gnu.org/software/make/)
+  [C compiler](https://gcc.gnu.org/)
+  [FORTRAN compiler](https://gcc.gnu.org/)
+  Optionally [MPI](https://openmpi.org/)


Building / Installation
-----------------------
`limits` has a simple `Makefile` and relies on `CC` and `FC` being set.
If you want to enable the optional MPI component, you will need to define
`HAVE_MPI` in both `CFLAGS` and `FCFLAGS`.
