#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "qarray.h"
#include "qlist.h"
#include "simul.h"
#include "test.h"

#define T1_A 0.0
#define T1_B 6.0
#define T2_A 0.0
#define T2_B 1.0

int main()
{
	double t1_a = T1_A, t1_b = T1_B;
	double t2_a = T2_A, t2_b = T2_B;
	
	srand(time(NULL));
	int action = -1;
	setbuf(stdout, NULL);
	printf("Programm is working with queues (static array and linked lists methods).\nEnter option menu:\n0 - exit\n1 - array method\n2 - list method\n3 - time experiment\n");
	int rc = scanf("%d", &action);
	if (rc != 1 || action > 3 || action < 0)
		printf("Wrong menu input!\n");
	else if (action == 0)
	{
		printf("Shutting down...\n");
		return EXIT_SUCCESS;
	}
	else if (action == 1)
	{
		printf("Enter T1 & T2 intervals: ");
		if (scanf("%lf%lf%lf%lf", &t1_a, &t1_b, &t2_a, &t2_b) != 4)
		{
			printf("Invalid input! Used standart values\n"
				"T1 = {%2.1f ; %2.1f}, T2 = {%2.1f ; %2.1f}\n",
				T1_A, T1_B, T2_A, T2_B);
			t1_a = T1_A;
			t1_b = T1_B;
			t2_a = T2_A;
			t2_b = T2_B;
		}
		simulate_arr(t1_a, t1_b, t2_a, t2_b);
	}
	else if (action == 2)
	{
		printf("Enter T1 & T2 intervals: ");
		if (scanf("%lf%lf%lf%lf", &t1_a, &t1_b, &t2_a, &t2_b) != 4)
		{
			printf("Invalid input! Used standart values\n"
				"T1 = {%2.1f ; %2.1f}, T2 = {%2.1f ; %2.1f}\n",
				T1_A, T1_B, T2_A, T2_B);
			t1_a = T1_A;
			t1_b = T1_B;
			t2_a = T2_A;
			t2_b = T2_B;
		}
		simulate_list(t1_a, t1_b, t2_a, t2_b);
	}
	else if (action == 3)
		test();
	return EXIT_SUCCESS;
}