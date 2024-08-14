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
    printf("|             Program is working with tree of words.             |\n");
    printf("------------------------------------------------------------------\n");
    printf("|\t0. Exit program.                                         |\n");
    printf("|\t1. Read file.                                            |\n");
    printf("|\t2. Add word.                                             |\n");
    printf("|\t3. Delete word.                                          |\n");
    printf("|\t4. Search the word.                                      |\n");
    printf("|\t5. Print tree's words in infix order.                    |\n");
    printf("|\t6. Search for words that start with character.           |\n");
    printf("|\t7. Draw a tree.                                          |\n");
    printf("|\t8. Calculate and compare time.                           |\n");
    printf("------------------------------------------------------------------\n");
}