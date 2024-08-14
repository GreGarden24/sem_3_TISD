#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "matrix_proc.h"
#include "matrix_io.h"
#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


int main(void)
{
	printf("\nProgramm is processing with matrix, to start choose the command:\n0) Exit the program\n1) Multiply matrix on vector by linked arrays method.\n2) Multiply matrix on vector by standart method.\n3) Compare work time for random matrix between standart and linked arrays method.\n");
	int menu;
	char choose[10];
	int ret_err;
	while(1)
	{	
		printf("Input command number: ");
		if (scanf("%d", &menu) != 1)
		{
			input_flush();
			printf("\nWrong menu option, try one more time!\n");
			continue;
		}

		switch (menu)
		{
			case 0:
			{	
				printf("Shutting down program...\n");
				return EXIT_SUCCESS;
			}
			case 1:
			{
				printf("Do you want to interact with files or keyboard? Input 'file' or 'key': ");
				scanf("%s", choose);
				while (strlen(choose) > 5 || (strcmp(choose, "file") && strcmp(choose, "key")))
				{
					printf("\nWrong option, try one more time!\n");
					input_flush();
					printf("\nInput 'file' or 'key': ");
					scanf("%s", choose);
				}
				input_flush();
				if (! strcmp(choose, "key"))
				{
					sparce_matrix matrix_A, matrix_B, matrix_C;


					printf("Input matrix A sizes: ");
					if (scanf("%d%d", &(matrix_A.row), &(matrix_A.col)) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					input_flush();
					while (matrix_A.row <= 0 || matrix_A.col <= 0)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &(matrix_A.row), &(matrix_A.col));
						input_flush();
					}

					matrix_A.not_zeros = 0;
					matrix_A.AN = calloc(matrix_A.row * matrix_A.col, M_SIZE);
					if (matrix_A.AN == NULL)
					{
						printf("Can't allocate AN!\n");
       					return MEMORY_ERROR;
					}
					matrix_A.AI = malloc(matrix_A.row * matrix_A.col * sizeof(int));
					if (matrix_A.AI == NULL)
					{
						free(matrix_A.AN);
						printf("Can't allocate AI!\n");
       					return MEMORY_ERROR;
					}
					matrix_A.AJ = malloc(matrix_A.col * sizeof(int));
					if (matrix_A.AJ == NULL)
					{
						free(matrix_A.AN);
						free(matrix_A.AI);
						printf("Can't allocate AJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < matrix_A.col; i++)
						matrix_A.AJ[i] = -1;
					///
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 5 || (strcmp(choose, "pos") && strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_sparse_key(&matrix_A);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_sparse_key(&matrix_A);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						int temp_ch;
						while (1)
						{
							printf("\nInput positions (input -1 -1 if you want to stop): ");
							temp_ch = scanf("%d%d", &it, &jt);
							input_flush();
							if (temp_ch  == 2 && it < matrix_A.row && jt < matrix_A.col)
							{
								if (it == -1 && jt == -1)
									break;
								printf("\nInput number: ");
								temp_ch = scanf("%lf", &tempd);
								input_flush();
								while (temp_ch != 1)
								{
									printf("\nWrong input! Try one more time!\n");
									printf("\nInput number: ");
									temp_ch = scanf("%lf", &tempd);
									input_flush();
								}
								matrix_A.AN[it * matrix_A.col + jt] = tempd;							
							}
							else
							{
								printf("\nWrong input! Try one more time!\n ");
							}
						}
						
						read_matrix_sparse_key_coord(&matrix_A);
					}
					///
					


					printf("Input vertical vector B sizes: ");
					
					if (scanf("%d%d", &(matrix_B.row), &(matrix_B.col)) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					while (matrix_B.row <= 0 || matrix_B.col != 1 || matrix_A.col  != matrix_B.row )
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &(matrix_B.row), &(matrix_B.col));
						input_flush();
					}


					matrix_B.not_zeros = 0;
					matrix_B.AN = calloc(matrix_B.row * matrix_B.col, M_SIZE);
					if (matrix_B.AN == NULL)
					{
						printf("Can't allocate BN!\n");
       					return MEMORY_ERROR;
					}
					matrix_B.AI = malloc(matrix_B.row * matrix_B.col * sizeof(int));
					if (matrix_B.AI == NULL)
					{
						free(matrix_B.AN);
						free(matrix_A.AN);
						free(matrix_A.AI);
						printf("Can't allocate BI!\n");
       					return MEMORY_ERROR;
					}
					matrix_B.AJ = malloc(matrix_B.col * sizeof(int));
					if (matrix_B.AJ == NULL)
					{
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						printf("Can't allocate BJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < matrix_B.col; i++)
						matrix_B.AJ[i] = -1;
					///
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					input_flush();
					while (strlen(choose) > 5 || ((strcmp(choose, "pos") && strcmp(choose, "all"))))
					{
						printf("\nWrong option, try one more time!\n");
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
						input_flush();
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_sparse_key(&matrix_B);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_sparse_key(&matrix_B);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						int temp_ch;
						while (1)
						{
							printf("\nInput positions (input -1 -1 if you want to stop): ");
							temp_ch = scanf("%d%d", &it, &jt);
							input_flush();
							if (temp_ch  == 2 && it < matrix_B.row && jt < matrix_B.col)
							{
								if (it == -1 && jt == -1)
									break;
								printf("\nInput number: ");
								temp_ch = scanf("%lf", &tempd);
								input_flush();
								while (temp_ch != 1)
								{
									printf("\nWrong input! Try one more time!\n");
									printf("\nInput number: ");
									temp_ch = scanf("%lf", &tempd);
									input_flush();
								}
								matrix_B.AN[it * matrix_B.col + jt] = tempd;							
							}
							else
							{
								printf("\nWrong input! Try one more time!\n ");
							}
						}
						read_matrix_sparse_key_coord(&matrix_B);
					}
					///

					printf("\nMatrix A:\n");
					print_matrix_sparse(matrix_A);
					printf("\nVector B:\n");
					print_matrix_sparse(matrix_B);

					matrix_C.not_zeros = 0;
					matrix_C.row = matrix_A.row;
					matrix_C.col = matrix_B.col;

					double *arr_C = calloc(matrix_A.row * matrix_B.col, M_SIZE);
					if (arr_C == NULL)
					{
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						printf("Can't allocate answer array C!\n");
       					return MEMORY_ERROR;
					}

					matrix_C.AN = malloc(matrix_A.row * matrix_B.col * M_SIZE);
					if (matrix_C.AN == NULL)
					{
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						free(arr_C);
						printf("Can't allocate CN!\n");
       					return MEMORY_ERROR;
					}
					matrix_C.AI = malloc(matrix_A.row * matrix_B.col * sizeof(int));
					if (matrix_C.AI == NULL)
					{
						free(matrix_C.AN);
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						free(arr_C);
						printf("Can't allocate CI!\n");
       					return MEMORY_ERROR;
					}
					matrix_C.AJ = malloc(matrix_B.col * sizeof(int));
					if (matrix_C.AJ == NULL)
					{
						free(matrix_C.AN);
						free(matrix_C.AI);
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						free(arr_C);
						printf("Can't allocate CJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < matrix_B.col; i++)
						matrix_C.AJ[i] = -1;
					
					mutiply_matrix_vector_sparse(matrix_A, matrix_B, &matrix_C, arr_C);
					printf("\nResult vector C:\n");
					print_matrix_sparse(matrix_C);

					free(matrix_A.AN);
					free(matrix_A.AI);
					free(matrix_A.AJ);
					free(matrix_B.AN);
					free(matrix_B.AI);
					free(matrix_B.AJ);
					free(arr_C);
					free(matrix_C.AN);
					free(matrix_C.AI);
					free(matrix_C.AJ);

				}
				else if (! strcmp(choose, "file"))
				{
					sparce_matrix matrix_A, matrix_B, matrix_C;
					char dir_A[30];
					char dir_B[30];

					matrix_A.not_zeros = 0;
					printf("Input file path with matrix A: ");
					scanf("%s", dir_A);

					FILE *fsrc_A = fopen(dir_A, "r");
					while (fsrc_A == NULL || (! strcmp(dir_A, "exit")))
					{
						if (! strcmp(dir_A, "exit"))
						{
							printf("Shutting down program...\n");
							return FILE_ERROR;
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_A);
						fsrc_A = fopen(dir_A, "r");
					}
					ret_err = read_matrix_sparce_file(fsrc_A, &matrix_A);
					if (ret_err != EXIT_SUCCESS)
					{
						printf("File is not capable of program needs!\n");
						continue;
					}
					printf("Matrix A readed!\n");
					fclose(fsrc_A);

					matrix_B.not_zeros = 0;
					printf("Input file path with vertical vector B: ");
					scanf("%s", dir_B);

					FILE *fsrc_B = fopen(dir_B, "r");
					while (fsrc_B == NULL || (! strcmp(dir_B, "exit")))
					{
						if (! strcmp(dir_B, "exit"))
						{
							printf("Shutting down program...\n");
							{	
								free(matrix_A.AN);
								free(matrix_A.AI);
								free(matrix_A.AJ);
								return FILE_ERROR;
							}
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_B);
						fsrc_B = fopen(dir_B, "r");
					}

					ret_err = read_matrix_sparce_file(fsrc_B, &matrix_B);
					if (ret_err != EXIT_SUCCESS)
					{
						printf("File is not capable of program needs!\n");
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						continue;
					}
					printf("Vector B readed!\n");
					fclose(fsrc_B);


					
					printf("\nMatrix A:\n");
					print_matrix_sparse(matrix_A);
					printf("\nVector B:\n");
					print_matrix_sparse(matrix_B);

					matrix_C.not_zeros = 0;
					matrix_C.row = matrix_A.row;
					matrix_C.col = matrix_B.col;

					double *arr_C = calloc(matrix_A.row * matrix_B.col, M_SIZE);
					if (arr_C == NULL)
					{
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						printf("Can't allocate answer array C!\n");
       					return MEMORY_ERROR;
					}

					matrix_C.AN = malloc(matrix_A.row * matrix_B.col * M_SIZE);
					if (matrix_C.AN == NULL)
					{
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						free(arr_C);
						printf("Can't allocate CN!\n");
       					return MEMORY_ERROR;
					}
					matrix_C.AI = malloc(matrix_A.row * matrix_B.col * sizeof(int));
					if (matrix_C.AI == NULL)
					{
						free(matrix_C.AN);
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						free(arr_C);
						printf("Can't allocate CI!\n");
       					return MEMORY_ERROR;
					}
					matrix_C.AJ = malloc(matrix_B.col * sizeof(int));
					if (matrix_C.AJ == NULL)
					{
						free(matrix_C.AN);
						free(matrix_C.AI);
						free(matrix_B.AN);
						free(matrix_B.AI);
						free(matrix_A.AN);
						free(matrix_A.AI);
						free(matrix_A.AJ);
						free(matrix_B.AJ);
						free(arr_C);
						printf("Can't allocate CJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < matrix_B.col; i++)
						matrix_C.AJ[i] = -1;
					
					mutiply_matrix_vector_sparse(matrix_A, matrix_B, &matrix_C, arr_C);
					printf("\nResult vector C:\n");
					print_matrix_sparse(matrix_C);

					{
					free(matrix_A.AN);
					free(matrix_A.AI);
					free(matrix_A.AJ);
					free(matrix_B.AN);
					free(matrix_B.AI);
					free(matrix_B.AJ);
					free(arr_C);
					free(matrix_C.AN);
					free(matrix_C.AI);
					free(matrix_C.AJ);
					}
				}
				break;
			}
			case 2:
			{
				printf("Do you want to interact with files or keyboard? Input 'file' or 'key': ");
				scanf("%s", choose);
				while (strlen(choose) > 5 || (strcmp(choose, "file") && strcmp(choose, "key")))
				{
					printf("\nWrong option, try one more time!\n");
					input_flush();
					printf("\nInput 'file' or 'key': ");
					scanf("%s", choose);
				}
				input_flush();
				if (! strcmp(choose, "key"))
				{
					int Ai, Aj, Bi, Bj;
					printf("Input matrix A sizes: ");
					if (scanf("%d%d", &Ai, &Aj) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					input_flush();
					while (Ai <= 0 || Aj <= 0)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Ai, &Aj);
						input_flush();
					}
					double *matrix_A = calloc(Ai * Aj, sizeof(M_SIZE));
					if (matrix_A == NULL)
					{
						printf("Can't allocate matrix A!\n");
						return MEMORY_ERROR;
					}
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 3 || (strcmp(choose, "pos") && strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_key(matrix_A, Ai, Aj);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_key(matrix_A, Ai, Aj);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						int temp_ch;
						while (1)
						{
							printf("\nInput positions (input -1 -1 if you want to stop): ");
							temp_ch = scanf("%d%d", &it, &jt);
							input_flush();
							if (temp_ch  == 2 && it < Ai && jt < Aj)
							{
								if (it == -1 && jt == -1)
									break;
								printf("\nInput number: ");
								temp_ch = scanf("%lf", &tempd);
								input_flush();
								while (temp_ch != 1)
								{
									printf("\nWrong input! Try one more time!\n");
									printf("\nInput number: ");
									temp_ch = scanf("%lf", &tempd);
									input_flush();
								}
								matrix_A[it * Ai + jt] = tempd;						
							}
							else
							{
								printf("\nWrong input! Try one more time!\n ");
							}
						}
					}
					printf("Input vertical vector B sizes: ");
					if (scanf("%d%d", &Bi, &Bj) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					while (Bi <= 0 || Bj != 1 || Aj != Bi)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Bi, &Bj);
						input_flush();
					}
					double *matrix_B = calloc(Bi * Bj, sizeof(M_SIZE));
					if (matrix_B == NULL)
					{
						printf("Can't allocate matrix B!\n");
						free(matrix_A);
						return MEMORY_ERROR;
					}
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 3 || (strcmp(choose, "pos") && strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_key(matrix_B, Bi, Bj);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_key(matrix_B, Bi, Bj);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						int temp_ch;
						while (1)
						{
							printf("\nInput positions (input -1 -1 if you want to stop): ");
							temp_ch = scanf("%d%d", &it, &jt);
							input_flush();
							if (temp_ch  == 2 && it < Bi && jt < Bj)
							{
								if (it == -1 && jt == -1)
									break;
								printf("\nInput number: ");
								temp_ch = scanf("%lf", &tempd);
								input_flush();
								while (temp_ch != 1)
								{
									printf("\nWrong input! Try one more time!\n");
									printf("\nInput number: ");
									temp_ch = scanf("%lf", &tempd);
									input_flush();
								}
								matrix_B[it * Bj + jt] = tempd;					
							}
							else
							{
								printf("\nWrong input! Try one more time!\n ");
							}
						}

					}
					if (Ai <= 20 && Aj <= 20)
					{
						printf("Matrix A:\n");
						print_matrix(matrix_A, Ai, Aj);
					}
					if (Bi <= 20 && Bj <= 20)
					{
						printf("Matrix B:\n");
						print_matrix(matrix_B, Bi, Bj);
					}
					double *array_C = malloc(Ai * Bj * sizeof(M_SIZE));
					if (array_C == NULL)
					{
						printf("Can't allocate result matrix!\n");
						free(matrix_A);
						free(matrix_B);
						return MEMORY_ERROR;
					}
					mutiply_matrixes_standart(matrix_A, Ai, Aj, matrix_B, Bj, array_C);
					printf("Result matrix:\n");

					sparce_matrix matrix_C;
					matrix_C.not_zeros = 0;
					matrix_C.row = Ai;
					matrix_C.col = Bj;
					if (matrix_C.row <= 20 && matrix_C.col <= 20)
						print_matrix(array_C, Ai, Bj);
					
					//
					matrix_C.AN = malloc(Ai * Bj * M_SIZE);
					if (matrix_C.AN == NULL)
					{
						free(matrix_A);
						free(matrix_B);
						free(array_C);
       					return MEMORY_ERROR;
					}
					matrix_C.AI = malloc(Ai * Bj * sizeof(int));
					if (matrix_C.AI == NULL)
					{
						free(matrix_C.AN);
						free(matrix_A);
						free(matrix_B);
						free(array_C);
						printf("Can't allocate CI!\n");
       					return MEMORY_ERROR;
					}
					matrix_C.AJ = malloc(Bj * sizeof(int));
					if (matrix_C.AJ == NULL)
					{
						free(matrix_C.AN);
						free(matrix_C.AI);
						free(matrix_A);
						free(matrix_B);
						free(array_C);
						printf("Can't allocate CJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < Bj; i++)
						matrix_C.AJ[i] = -1;
					//
					for (int i = 0; i < Ai; i++)
					{
						if (fabs(array_C[i]) > 1e-16)
						{
							(matrix_C.AN)[(matrix_C.not_zeros)++] = array_C[i];
							(matrix_C.AI)[(matrix_C.not_zeros) - 1] = i;
							if ((matrix_C.AJ)[i] == -1)
									(matrix_C.AJ)[i] = (matrix_C.not_zeros) - 1;
						}
					}
					print_matrix_sparse(matrix_C);
					free(matrix_A);
					free(matrix_B);
					free(array_C);
					free(matrix_C.AN);
					free(matrix_C.AI);
					free(matrix_C.AJ);
				}
				else if (! strcmp(choose, "file"))
				{
					int Ai, Aj, Bi, Bj;
					char dir_A[30];
					char dir_B[30];
					double *matrix_A, *matrix_B, *matrix_C;
					printf("Input file path with matrix A: ");
					scanf("%s", dir_A);

					FILE *fsrc_A = fopen(dir_A, "r");
					while (fsrc_A == NULL || (! strcmp(dir_A, "exit")))
					{
						if (! strcmp(dir_A, "exit"))
						{
							printf("Shutting down program...\n");
							return FILE_ERROR;
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_A);
						fsrc_A = fopen(dir_A, "r");
					}

					ret_err = read_matrix_file(fsrc_A, &matrix_A, &Ai, &Aj);
					if (ret_err != EXIT_SUCCESS)
					{
						printf("File is not capable of program needs!\n");
						continue;
					}
					printf("Matrix readed!\n");
					fclose(fsrc_A);

					printf("Input file path with vertical vector B: ");
					scanf("%s", dir_B);
					FILE *fsrc_B = fopen(dir_B, "r");
					while (fsrc_B == NULL || (! strcmp(dir_B, "exit")))
					{
						if (! strcmp(dir_B, "exit"))
						{
							printf("Shutting down program...\n");
							return FILE_ERROR;
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_B);
					}
					ret_err = read_matrix_file(fsrc_B, &matrix_B, &Bi, &Bj);
					if (ret_err != EXIT_SUCCESS)
					{
						fclose(fsrc_B);
						printf("File is not capable of program needs!\n");
						continue;
					}
					if (Bj != 1)
					{
						printf("Vector's width is not 1!\n");
						free(matrix_A);
						free(matrix_B);
						continue;
					}
					printf("Vector readed!\n");
					fclose(fsrc_B);
					
					if (Aj != Bi)
					{
						printf("Matrix can't be multiplied!\n");
						free(matrix_A);
						free(matrix_B);
						continue;
					}
					matrix_C = malloc(Ai * Bj * M_SIZE);
					if (matrix_C == NULL)
					{
						printf("Can't allocate result matrix!\n");
       					return MEMORY_ERROR;
					}

					mutiply_matrixes_standart(matrix_A, Ai, Aj, matrix_B, Bj, matrix_C);
					printf("Result matrix:\n");
					print_matrix(matrix_C, Ai, Bj);

					free(matrix_A);
					free(matrix_B);
					free(matrix_C);
				}
				break;
			}
			case 3:
			{
				int row, col, percent;
				printf("Input row and col sizes for random matrix: ");
				scanf("%d%d", &row, &col);
				input_flush();
				printf("Input percentage of zeros: ");
				scanf("%d", &percent);
				input_flush();
				if (generate_rand_matrix("matrix_A.txt", row, col, percent) != EXIT_SUCCESS)
				{
					printf("Cant generate file with random matrix!\n");
					continue;
				}
				if (generate_rand_matrix("vector_B.txt", row, 1, 0) != EXIT_SUCCESS)
				{
					printf("Cant generate file with random vector!\n");
					continue;
				}
				sparce_matrix matrix_A, matrix_B, matrix_C;
				matrix_A.not_zeros = 0;
				matrix_A.row = row;
				matrix_A.col = col;
				
				matrix_B.not_zeros = 0;
				matrix_B.row = col;
				matrix_B.col = 1;

				int mem_A, mem_B, mem_C;
				int mem_A_sparce, mem_B_sparce, mem_C_sparce;
				// подcчет времени и памяти для разреженного метода
				FILE *fsrc_A = fopen("matrix_A.txt", "r");
				read_matrix_sparce_file(fsrc_A, &matrix_A);
				mem_A_sparce = row * col * M_SIZE + row * col * sizeof(int) + col * sizeof(int);

				FILE *fsrc_B = fopen("vector_B.txt", "r");
				read_matrix_sparce_file(fsrc_B, &matrix_B);
				mem_B_sparce = row * 1 * M_SIZE + row * 1 * sizeof(int) + 1 * sizeof(int);


				matrix_C.not_zeros = 0;
				double *arr_C = calloc(row * 1, M_SIZE);
				if (arr_C == NULL)
				{
					free(matrix_B.AN);
					free(matrix_B.AI);
					free(matrix_A.AN);
					free(matrix_A.AI);
					free(matrix_A.AJ);
					free(matrix_B.AJ);
					printf("Can't allocate answer array C!\n");
       				return MEMORY_ERROR;
				}
				matrix_C.AN = malloc(row * 1 * M_SIZE);
				if (matrix_C.AN == NULL)
				{
					free(matrix_B.AN);
					free(matrix_B.AI);
					free(matrix_A.AN);
					free(matrix_A.AI);
					free(matrix_A.AJ);
					free(matrix_B.AJ);
					free(arr_C);
					printf("Can't allocate CN!\n");
       				return MEMORY_ERROR;
				}
				matrix_C.AI = malloc(row * 1 * sizeof(int));
				if (matrix_C.AI == NULL)
				{
					free(matrix_C.AN);
					free(matrix_B.AN);
					free(matrix_B.AI);
					free(matrix_A.AN);
					free(matrix_A.AI);
					free(matrix_A.AJ);
					free(matrix_B.AJ);
					free(arr_C);
					printf("Can't allocate CI!\n");
       				return MEMORY_ERROR;
				}
				matrix_C.AJ = malloc(1 * sizeof(int));
				if (matrix_C.AJ == NULL)
				{
					free(matrix_C.AN);
					free(matrix_C.AI);
					free(matrix_B.AN);
					free(matrix_B.AI);
					free(matrix_A.AN);
					free(matrix_A.AI);
					free(matrix_A.AJ);
					free(matrix_B.AJ);
					free(arr_C);
					printf("Can't allocate CJ!\n");
       				return MEMORY_ERROR;
				}
				for (int i = 0; i < 1; i++)
					matrix_C.AJ[i] = -1;
				
				mem_C_sparce = row * 1 * M_SIZE + row * 1 * M_SIZE + row * 1 * sizeof(int) + 1 * sizeof(int);

				struct timespec t_beg, t_end;
				unsigned long long sparce_time, standart_time;
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
				mutiply_matrix_vector_sparse(matrix_A, matrix_B, &matrix_C, arr_C);
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	

				
				sparce_time = calc_elapsed_time(&t_beg, &t_end);
				free(matrix_A.AN);
				free(matrix_A.AI);
				free(matrix_A.AJ);
				free(matrix_B.AN);
				free(matrix_B.AI);
				free(matrix_B.AJ);
				free(arr_C);
				free(matrix_C.AN);
				free(matrix_C.AI);
				free(matrix_C.AJ);		
				

				// подcчет времени и памяти для стандартного метода
				rewind(fsrc_A);
				rewind(fsrc_B);
				double *array_A, *array_B, *array_C;
				read_matrix_file(fsrc_A, &array_A, &row, &col);
				mem_A = row * col * M_SIZE;
				fclose(fsrc_A);
				int Bj;
				read_matrix_file(fsrc_B, &array_B, &col, &Bj);
				mem_B = row * 1 * M_SIZE;
				fclose(fsrc_B);

				array_C = malloc(row * 1 * M_SIZE);
				if (array_C == NULL)
				{
					printf("Can't allocate result matrix!\n");
       				return MEMORY_ERROR;
				}

				mem_C = row * 1 * M_SIZE;
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
				mutiply_matrixes_standart(array_A, row, col, array_B, Bj, array_C);
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	

				
				standart_time = calc_elapsed_time(&t_beg, &t_end);
				free(array_A);
				free(array_B);
				free(array_C);
				

				printf("\nFor standart method was used bytes:\n");
				printf("For matrix A: %10d\n", mem_A);
				printf("For vector B: %10d\n", mem_B);
				printf("For vector C: %10d\n", mem_C);
				printf("\nIn total was used: %10d bytes or %10.1lf Kbytes or %10.1lf Gbytes\n", mem_A + mem_B + mem_C, (mem_A + mem_B + mem_C) / 1024.0, (mem_A + mem_B + mem_C) / 1024.0 / 1024.0);

				printf("\nFor linked arrays method was used bytes:\n");
				printf("For matrix A: %10d\n", mem_A_sparce);
				printf("For vector B: %10d\n", mem_B_sparce);
				printf("For vector C: %10d\n", mem_C_sparce);
				printf("\nIn total was used: %10d bytes or %10.1lf Kbytes or %10.1lf Gbytes\n", mem_A_sparce + mem_B_sparce + mem_C_sparce, (mem_A_sparce + mem_B_sparce + mem_C_sparce) / 1024.0, (mem_A_sparce + mem_B_sparce + mem_C_sparce) / 1024.0 / 1024.0);

				printf("\nTime that was used to multiply matrix on vector in microseconds:\n");
				printf("| standart: %15lld | linked arrays: %15lld |\n", standart_time ,sparce_time);


				FILE *fdst_st, *fdst_sp;
				fdst_st = fopen("time_for_standart.txt", "a+");
				fdst_sp = fopen("time_for_sparce.txt", "a+");
				fprintf(fdst_st, "%d %d %d %lld\n", row, col, percent, standart_time);
				fprintf(fdst_sp, "%d %d %d %lld\n", row, col, percent, sparce_time);
				fclose(fdst_st);
				fclose(fdst_sp);
				break;
			}
			default:
			{
				input_flush();
				printf("\nWrong menu option, try one more time!\n");
				continue;
			}
		}
	}

	return EXIT_SUCCESS;
}
