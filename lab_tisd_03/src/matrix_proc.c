#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix_proc.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


void mutiply_matrixes_standart(double *matrix_A, int Ai, int Aj, double *matrix_B, int Bj, double *matrix_C)
{
    double elem = 0;
    for (int i = 0; i < Ai; i++)
        for (int j = 0; j < Bj; j++)
        {
            for (int k = 0; k < Aj; k++)
                elem += matrix_A[i * Aj + k] * matrix_B[k * Bj + j];

            matrix_C[i * Bj + j] = elem;
            elem = 0;
        }
}

void mutiply_matrix_vector_sparse(sparce_matrix matrix_A, sparce_matrix matrix_B, sparce_matrix *matrix_C, double *arr_C)
{
    int start;
    int stop;
    for (int i = 0; i < matrix_B.not_zeros; i++)
    {
        start = (matrix_A.AJ)[(matrix_B.AI)[i]];
        if (start != -1)
        {
            stop = matrix_A.not_zeros;
            for (int j = (matrix_B.AI)[i] + 1; j < matrix_A.col; j++)
                if ((matrix_A.AJ)[j] != -1)
                {
                    stop = (matrix_A.AJ)[j];
                    break;
                }

            for (int j = start; j < stop; j++)
                arr_C[(matrix_A.AI)[j]] += (matrix_A.AN)[j] * (matrix_B.AN)[i];
        }   
    }

    for (int i = 0; i < matrix_A.row; i++)
    {
        if (fabs(arr_C[i]) > 1e-16)
        {
            (matrix_C->AN)[(matrix_C->not_zeros)++] = arr_C[i];
            (matrix_C->AI)[(matrix_C->not_zeros) - 1] = i;
            if ((matrix_C->AJ)[i] == -1)
                    (matrix_C->AJ)[i] = (matrix_C->not_zeros) - 1;
        }
    }
}
