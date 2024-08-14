#ifndef __MATRIX_PROC_H__
#define __MATRIX_PROC_H__


typedef struct
{
    int row, col;
    int not_zeros;
    double *AN;
    int *AI;
    int *AJ;
} sparce_matrix;

void mutiply_matrixes_standart(double *matrix_A, int Ai, int Aj, double *matrix_B, int Bj, double *matrix_C);
void mutiply_matrix_vector_sparse(sparce_matrix matrix_A, sparce_matrix matrix_B, sparce_matrix *matrix_C, double *arr_C);

#endif // __MATRIX_PROC_H__