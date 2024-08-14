#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include "time_exp.h"
#include "matrix_io.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long) (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec)) / 1000; 
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int generate_rand_matrix(char *file_name, int row, int col, int percentage)
{
	if (percentage > 100 || percentage < 0)
		return EXIT_FAILURE;
	srand(time(NULL));
	FILE *fdst = fopen(file_name, "w");
	if (fdst == NULL)
		return FILE_ERROR;
	
	int zeros = (int)(percentage / 100.0 * row * col);
	fprintf(fdst, "%d %d\n", row, col);

	double *matrix = malloc(row * col * M_SIZE);
	if (matrix == NULL)
		return MEMORY_ERROR;
	
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
			matrix[i * row + j] = randfrom(-100000, 100000);

	int itemp, jtemp;
	for (int i = 0; i < zeros; i++)
	{
		itemp = rand() % row;
		jtemp = rand() % col;
		while (fabs(matrix[itemp * row + jtemp]) < 1e-16)
		{
			itemp = rand() % row;
			jtemp = rand() % col;
		}
		matrix[itemp * row + jtemp] = 0;
	}


	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			fprintf(fdst, "%.6lf", matrix[i * row + j]);
			if (j != row - 1)
				fprintf(fdst, " ");
		}
		fprintf(fdst, "\n");
	}

	free(matrix);
	fclose(fdst);
	return EXIT_SUCCESS;
}
