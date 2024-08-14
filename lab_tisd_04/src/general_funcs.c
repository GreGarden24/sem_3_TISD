#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "general_funcs.h"

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

void print_menu(void)
{
    printf("------------------------------------------------------------------\n");
    printf("|            Program is working with stack of words.             |\n");
    printf("------------------------------------------------------------------\n");
    printf("|\t0. Exit program.                                         |\n");
    printf("|\t1. Add word.                                             |\n");
    printf("|\t2. Delete word.                                          |\n");
    printf("|\t3. Print all words.                                      |\n");
    printf("|\t4. Print all reversed words in revers order.             |\n");
    printf("|\t5. Calculate and compare time.                           |\n");
    printf("------------------------------------------------------------------\n");
}