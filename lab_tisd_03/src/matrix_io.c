#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix_io.h"
#include "matrix_proc.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

void input_flush(void)
{
    char check;
    scanf("%c", &check);
    for (char check1 = check; check1 != '\n'; scanf("%c", &check1)){}
}

int read_matrix_key(double *matrix, int row, int col)
{
    double elem;
    printf("Input matrix with %d rows and %d colums:\n\n", row, col);
    for (int i = 0; i < row; i++)
    {
        printf("Input %d'th row: ", i + 1);
        for (int j = 0; j < col; j++)
        {
            if (scanf("%lf", &elem) != 1)
            {
               printf("Wrong input!\n");
               return EXIT_FAILURE; 
            }
            matrix[i * col + j] = elem;
        }
    }
    input_flush();
    return EXIT_SUCCESS;
}

void print_matrix(double *matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%15.6lf", matrix[i * col + j]);
        printf("\n");
    }
    printf("\n");
}

int read_matrix_file(FILE *fsrc, double **matrix, int *row, int *col)
{
    if (fscanf(fsrc, "%d%d", row, col) != 2)
        return FILE_ERROR;
    char check;
    fscanf(fsrc, "%c", &check);
    if (check != '\n')
        return FILE_ERROR;
    if ((*row) <= 0 || (*col) <= 0)
    	return FILE_ERROR;
    *matrix = malloc((*row) * (*col) * M_SIZE);
    if (*matrix == NULL)
        return MEMORY_ERROR;
    double elem;
    for (int i = 0; i < (*row); i++)
    {
        for (int j = 0; j < (*col); j++)
        {
            if (fscanf(fsrc, "%lf", &elem) != 1)
                return FILE_ERROR;
            (*matrix)[i * (*col) + j] = elem;
        }
        fscanf(fsrc, "%c", &check);
        if (check != '\n')
            return FILE_ERROR;
    }
    fscanf(fsrc, "%c", &check);
        if (check != '\n')
            return FILE_ERROR;
    if (! feof(fsrc))
        return FILE_ERROR;

    return EXIT_SUCCESS;
}




int read_matrix_sparse_key(sparce_matrix *matrix_A)
{
    double elem;
    printf("Input matrix with %d rows and %d colums:\n\n", matrix_A->row, matrix_A->col);
    for (int i = 0; i < matrix_A->col; i++)
    {
        printf("Input %d'th col: ", i + 1);
        for (int j = 0; j < matrix_A->row; j++)
        {
            if (scanf("%lf", &elem) != 1)
            {
               printf("Wrong input!\n");
               return EXIT_FAILURE; 
            }
            if (fabs(elem) > 1e-16)
            {
                matrix_A->AN[matrix_A->not_zeros++] = elem;
                matrix_A->AI[matrix_A->not_zeros - 1] = j;
                if (matrix_A->AJ[i] == -1)
                    matrix_A->AJ[i] = matrix_A->not_zeros - 1;
            }
        }
        input_flush();
    }
    return EXIT_SUCCESS;
}

int read_matrix_sparse_key_coord(sparce_matrix *matrix_A)
{
    double elem;
    for (int i = 0; i < matrix_A->col; i++)
    {
        for (int j = 0; j < matrix_A->row; j++)
        {
            elem = matrix_A->AN[i * matrix_A->row + j];
            if (fabs(elem) > 1e-16)
            {
                matrix_A->AN[matrix_A->not_zeros++] = elem;
                matrix_A->AI[matrix_A->not_zeros - 1] = j;
                if (matrix_A->AJ[i] == -1)
                    matrix_A->AJ[i] = matrix_A->not_zeros - 1;
            }
        }
    }
    return EXIT_SUCCESS;
}

void print_matrix_sparse(sparce_matrix matrix_A)
{
    printf("Array with not zero elemets:\n");
    for (int i = 0; i < matrix_A.not_zeros; i++)
        printf("%15.6lf", matrix_A.AN[i]);
    printf("\nArray with their rows:\n");
    for (int i = 0; i < matrix_A.not_zeros; i++)
        printf("%d ", matrix_A.AI[i]);
    printf("\nLinked array with positions of number that went first in column:\n");
    for (int i = 0; i < matrix_A.col; i++)
        printf("%d ", matrix_A.AJ[i]);
    printf("\n");
    
}

int read_matrix_sparce_file(FILE *fsrc, sparce_matrix *matrix_A)
{
    if (fscanf(fsrc, "%d%d", &(matrix_A->row), &(matrix_A->col)) != 2)
        return FILE_ERROR;
    char check;
    fscanf(fsrc, "%c", &check);
    if (check != '\n')
        return FILE_ERROR;
    if (matrix_A->row <= 0 || matrix_A->col <= 0)
    	return FILE_ERROR;
    	
    matrix_A->AN = malloc(matrix_A->row * matrix_A->col * M_SIZE);
	if (matrix_A->AN == NULL)
       	return MEMORY_ERROR;

	matrix_A->AI = malloc(matrix_A->row * matrix_A->col * sizeof(int));
	if (matrix_A->AI == NULL)
	{
		free(matrix_A->AN);
       	return MEMORY_ERROR;
	}

	matrix_A->AJ = malloc(matrix_A->col * sizeof(int));
	if (matrix_A->AJ == NULL)
	{
		free(matrix_A->AN);
		free(matrix_A->AI);
       	return MEMORY_ERROR;
	}
	for (int i = 0; i < matrix_A->col; i++)
	    (matrix_A->AJ)[i] = -1;

    double elem;
    for (int i = 0; i < matrix_A->col; i++)
    {
        for (int j = 0; j < matrix_A->row; j++)
        {
            if (fscanf(fsrc, "%lf", &elem) != 1)
               return FILE_ERROR;
            if (fabs(elem) > 1e-16)
            {
                (matrix_A->AN)[(matrix_A->not_zeros)++] = elem;
                (matrix_A->AI)[(matrix_A->not_zeros) - 1] = j;
                if ((matrix_A->AJ)[i] == -1)
                    (matrix_A->AJ)[i] = (matrix_A->not_zeros) - 1;
            }
        }
    }
    return EXIT_SUCCESS;
}


