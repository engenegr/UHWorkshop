#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <mpi.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* Specify number of grid points in x and y directions */
#define IX 128
#define IY 128

/* MPI variables */
#define MASTER (rank == 0)
#define NODE (rank != 0)
#define LAST_NODE (rank == nprocs - 1)
#define WORLD MPI_COMM_WORLD

struct Grid2D {
  /* Two arrays are required for each Variable; one for old time step and one
   * for the new time step. */
  double **ubufo;
  double **ubufn;
  double **vbufo;
  double **vbufn;
  double **pbufo;
  double **pbufn;

  /* Grid Spacing */
  double dx;
  double dy;

  /* Number of rows in each node */
  int nrows;
  int nrows_ex;
  int ghosts;
} g;

struct FieldPointers {
  /* Two pointers to the generated buffers for each variable */
  double **u;
  double **un;
  double **v;
  double **vn;
  double **p;
  double **pn;
} f;

struct SimulationInfo {
  /* Boundary conditions */
  double ubc[4];
  double vbc[4];
  double pbc[4];

  /* Flow parameters based on inputs */
  double dt;
  double nu;
  double c2;
  double cfl;

  /*  Neighbor partitions */
  int prev;
  int next;
} s;

/* Generate a 2D array using pointer to a pointer */
double **array_2D(int row, int col);

/* Update the fields to the new time step for the next iteration */
void update(struct FieldPointers *f);

/* Applying boundary conditions for velocity */
void set_UBC(struct FieldPointers *f, struct Grid2D *g,
             struct SimulationInfo *s, int rank, int nprocs);

/* Applying boundary conditions for pressure */
void set_PBC(struct FieldPointers *f, struct Grid2D *g,
             struct SimulationInfo *s, int rank, int nprocs);

/* Free the memory */
void freeMem(double **phi, ...);

/* Find mamximum of a set of float numebrs */
double fmaxof(double errs, ...);

/* Save fields data to files */
void dump_data(struct Grid2D *g, struct SimulationInfo *s);

#endif /* FUNCTIONS_H */
