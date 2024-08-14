#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qlist.h"
#include "error.h"
#include "qarray.h"
#include "simul.h"


#define ARR_SIZE_BIG 1000

typedef unsigned long int tick_t;

tick_t tick(void)
{
	tick_t d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

int time_measure(int len)
{
	int rc = EXIT_SUCCESS;
	tick_t start = 0, end = 0;
	
	tick_t tpush_list = 0, tpop_list = 0;
	tick_t tpush_arr = 0, tpop_arr = 0;
	
	for (int j = 0; j < 1000; j++)
	{
		list *pin = NULL, *pout = NULL;
		for (int k = 0; k < len; k++)
		{
			int d = rand() % 100 - 50;
			start = tick();
			rc = push_qlist(d, &pin, &pout);
			end = tick();
			if (rc != EXIT_SUCCESS)
				return rc;
			tpush_list += end - start;
		}
		
		for (int k = 0; k < len; k++)
		{
			start = tick();
			pop_qlist(&pin, &pout);
			end = tick();
			tpop_list += end - start;
		}
	}
	tpush_list /= 1000;
	tpop_list /= 1000;
	printf("%6lu %6lu ", tpush_list, tpop_list);
	
	for (int j = 0; j < 1000; j++)
	{
		int arr[ARR_SIZE_BIG], arr_k = 0;
		int *qb = arr, *qe = arr + ARR_SIZE_BIG;
		int *pin = arr, *pout = arr;
		for (int k = 0; k < len; k++)
		{
			int d = rand() % 100 - 50;
			start = tick();
			rc = push_qarr(d, &pin, &pout, &arr_k, qb, qe);
			end = tick();
			if (rc != EXIT_SUCCESS)
				return rc;
			tpush_arr += end - start;
		}
		
		for (int k = 0; k < len; k++)
		{
			start = tick();
			pop_qarr(&pout, &arr_k, qb, qe);
			end = tick();
			tpop_arr += end - start;
		}
	}
	tpush_arr /= 1000;
	tpop_arr /= 1000;
	printf("%6lu %6lu ", tpush_arr, tpop_arr);
	
	size_t mem_list = len * sizeof(list);
	size_t mem_arr = len * sizeof(int) + 4 * sizeof(int *);
	double tpush_eff = ((double)tpush_arr - tpush_list) / tpush_arr * 100;
	double tpop_eff = ((double)tpop_arr - tpop_list) / tpop_arr * 100;
	double mem_eff = ((double)mem_arr - mem_list) / mem_arr * 100;
	printf("%7.2f%% %7.2f%% %8lu %8lu %7.2f%%\n",
		tpush_eff, tpop_eff, (long int)mem_list, (long int)mem_arr, mem_eff);
	
	return rc;
}

int main()
{
	srand(time(NULL));
	int rc = EXIT_SUCCESS;
	setbuf(stdout, NULL);
	int arrk[] = { 1, 5, 10, 20, 40, 75, 100, 250, 500, 1000 };
	printf("%4s %13s %13s %17s %25s\n", "Len", "Stack by list",
		"Stack by array", "Time eff", "Memory eff");
	printf("%4s %6s %6s %6s %6s %8s %8s %8s %8s\n\n", " ",
		"push", "pop", "push", "pop", "push", "pop", "list", "arr");
	for (size_t i = 0; i < sizeof(arrk)/sizeof(arrk[0]); i++)
	{
		printf("%4d ", arrk[i]);
		rc = time_measure(arrk[i]);
		if (rc != EXIT_SUCCESS)
			errmsg(rc);
	}
	return rc;
}	
