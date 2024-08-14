#ifndef __MATRIX_IO_H__
#define __MATRIX_IO_H__

#define M_SIZE sizeof(double)

#include "matrix_proc.h"

int read_matrix_key(double *matrix, int row, int col);
void print_matrix(double *matrix, int row, int col);
void input_flush(void);
int read_matrix_file(FILE *fsrc, double **matrix, int *row, int *col);

int read_matrix_sparse_key(sparce_matrix *matrix_A);
void print_matrix_sparse(sparce_matrix matrix_A);
int read_matrix_sparse_key_coord(sparce_matrix *matrix_A);

int read_matrix_sparce_file(FILE *fsrc, sparce_matrix *matrix_A);


#endif // __MATRIX_IO_H__