#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#include "process.h"
#include "prints.h"


void print_number_t(number_t *number)
{
	printf("%c0.", number->sign);
	for (size_t i = 0; number->significant[i] != -1; i++)
		printf("%d", number->significant[i]);
	printf(" E ");
	printf("%d", number->exponent);
}

void print_answer_t(answer_t *answer)
{
	printf("%c0.", answer->sign);

	size_t start = 0;
	for (size_t i = 0; answer->significant[i] != -1; i++)
		start++;
	for (size_t i = start + 1; answer->significant[i] != -1; i++)
		printf("%d", answer->significant[i]);

	printf(" E ");
	printf("%d\n", answer->exponent);
}

void print_info(void)
{
	printf("Данная программа моделирует операцию умножения целого числа длиной до 30 десятичных цифр на\nдействительное число в форме +/- m.n E +/- K, где суммарная длина мантиссы m+n содержит до 30\nзначащих цифр, а величина порядка K - до 5 цифр. Результат выдается в форме +/- 0.m1 E +/- K1,\nгде m1 - до 30 значащих цифр, а K1 - до 5 цифр.\n");
}

void print_input_error_message(int error)
{
	switch (error)
	{
		case 2:
			printf("Число не было введено - пустой ввод!\n");
			break;
		case 3:
			printf("Число не было введено - не допустимый символ!\n");
			break;
		case 4:
			printf("Число не было введено - допустимая длина мантиссы или экспоненты была превышена!\n");
			break;
	}
}