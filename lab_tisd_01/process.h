#ifndef __PROCESS_H__
#define __PROCESS_H__

#define M_SIGNIFICANT 30
#define M_EXPONENT 5

#define EMPTY_INPUT 2
#define WRONG_CHARACTER 3
#define INPUT_FAILURE 4
#define TOO_BIG_EXP 5

typedef struct     
{
	char sign;
	int significant[M_SIGNIFICANT + 2];
	int exponent;
} number_t;             // структура данных, которая хранит в себе вводимые числа в стандартном виде

typedef struct
{
	char sign;
	int significant[M_SIGNIFICANT * 2 + 2 + 1];
	int exponent;
} answer_t;            // структура данных результата вычислений

int input_integer(number_t *src_integer);
int input_float(number_t *src_float);
int multiply_integer_float(number_t *src_integer, number_t *src_float, answer_t *dst_answer);

#endif // __PROCESS_H__