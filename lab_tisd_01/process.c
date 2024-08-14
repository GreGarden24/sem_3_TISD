#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#include "process.h"
#include "prints.h"

int input_integer(number_t *src_integer)
{
	char temp;
	if (scanf("%c", &temp) != 1 || temp == '\n')
		return EMPTY_INPUT;
	while (temp == ' ')
		if (scanf("%c", &temp) != 1 || temp == '\n')
			return EMPTY_INPUT;

	size_t digits = 0;
	size_t zeros_digits = 0;
	{
	src_integer->sign = '+';
	if (temp == '-')
		src_integer->sign = '-'; 
	else if (isdigit(temp))
	{
		if (temp != '0')
		{
			digits++;
			src_integer->significant[digits - 1] = (temp - '0');
		}
	}
	else if (temp != ' ' && temp != '+')
		return WRONG_CHARACTER;
	}
	if (scanf("%c", &temp) != 1)
		return WRONG_CHARACTER;

	while (temp != '\n')
	{
		if (isdigit(temp))
		{
			if (temp == '0' && digits != 0)
			{
				zeros_digits++;
				digits++;
				src_integer->significant[digits - 1] = 0;
			}
			else if (temp != '0')
			{
				zeros_digits = 0;
				digits++;
				src_integer->significant[digits - 1] = (temp - '0');
			}
		}
		else if (temp != ' ')
			return WRONG_CHARACTER;
		
		if (digits > M_SIGNIFICANT)
			return INPUT_FAILURE;

		if (scanf("%c", &temp) != 1)
			return WRONG_CHARACTER;
	}
	if (digits == 0)
	{
		digits++;
		src_integer->significant[digits - 1] = 0;
	}
	src_integer->significant[digits - zeros_digits] = -1;
	src_integer->exponent = digits;
	return EXIT_SUCCESS;
}

int input_float(number_t *src_float)
{
	src_float->exponent = 0;
	char temp;
	if (scanf("%c", &temp) != 1 || temp == '\n')
		return EMPTY_INPUT;
	while (temp == ' ')
		if (scanf("%c", &temp) != 1 || temp == '\n')
			return EMPTY_INPUT;
	
	size_t significant_digits = 0;
	size_t zeros_digits = 0;
	size_t exp_add = 0;
	size_t dot_flag = 0;

	{
	src_float->sign = '+';
	if (temp == '-')
		src_float->sign = '-'; 
	else if (isdigit(temp))
	{
		if (temp != '0')
		{
			significant_digits++;
			src_float->significant[significant_digits - 1] = (temp - '0');
		}
	}
	else if (temp == '.')
		dot_flag = 1;
	else if (temp != ' ' && temp != '+')
		return WRONG_CHARACTER;

	if (scanf("%c", &temp) != 1)
		return INPUT_FAILURE;
	}

	while (temp != '\n')
	{
		if (isdigit(temp))
		{
			if (temp == '0')
				zeros_digits++;
			else
			{
				if (dot_flag && significant_digits != 0)
					for (size_t i = 0; i < zeros_digits; i++)
					{
						significant_digits++;
						src_float->significant[significant_digits - 1] = 0;
					}
				else if (dot_flag && significant_digits == 0)
				{
					exp_add = -1 * zeros_digits;
				}

				zeros_digits = 0;
				significant_digits++;
				src_float->significant[significant_digits - 1] = (temp - '0');
			}
		}
		else if (temp == '.')
		{
			if (dot_flag)
				return WRONG_CHARACTER;
			if (significant_digits != 0)
			{
				exp_add = significant_digits + zeros_digits;
				for (size_t i = 0; i < zeros_digits; i++)
				{
					significant_digits++;
					src_float->significant[significant_digits - 1] = 0;
				}
			}
			dot_flag = 1;
			zeros_digits = 0;
		}
		else if (temp == 'e' || temp == 'E')
		{
			
			if (! dot_flag && significant_digits != 0)
				exp_add = significant_digits + zeros_digits;

			zeros_digits = 0;

			int exp_sign = 1;
			int exp_digits = 0;
			char exp_char[M_EXPONENT + 1];

			if (scanf("%c", &temp) != 1 || temp == '\n')
				return INPUT_FAILURE;
			while (temp == ' ')
				if (scanf("%c", &temp) != 1 || temp == '\n')
					return INPUT_FAILURE;

			if (temp == '-')
				exp_sign = -1;
			else if (isdigit(temp))
			{	
				if (temp != '0')
				{	
					exp_digits++;
					exp_char[exp_digits - 1] = temp;
				}
			}
			else if (temp != ' ' && temp != '+')
				return WRONG_CHARACTER;
			
			if (scanf("%c", &temp) != 1)
				return INPUT_FAILURE;

			while (temp != '\n')
			{
				if (isdigit(temp))
				{
					if (temp == '0' && exp_digits != 0)
					{
						exp_digits++;
						exp_char[exp_digits - 1] = '0';
					}
					else
					{
						exp_digits++;
						exp_char[exp_digits - 1] = temp;
					}
				}
				else if (temp != ' ')
					return INPUT_FAILURE;

				if (exp_digits > M_EXPONENT)
					return INPUT_FAILURE;

				if (scanf("%c", &temp) != 1)
					return INPUT_FAILURE;
			}
			exp_char[exp_digits] = '\0';
			src_float->exponent = exp_sign * atoi(exp_char) + exp_add;
			if (significant_digits == 0)
			{
				significant_digits++;
				src_float->significant[significant_digits - 1] = 0;
			}
			src_float->significant[significant_digits] = -1;
			return EXIT_SUCCESS;
		}
		else if (temp != ' ')
			return WRONG_CHARACTER;
		
		if (significant_digits > M_SIGNIFICANT)
			return INPUT_FAILURE;

		if (scanf("%c", &temp) != 1)
			return WRONG_CHARACTER;
	}
	if (! dot_flag && significant_digits != 0)
		exp_add = significant_digits + zeros_digits;
	src_float->exponent = exp_add;
	if (significant_digits == 0)
		{
			significant_digits++;
			src_float->significant[significant_digits - 1] = 0;
		}
	src_float->significant[significant_digits] = -1;
	return EXIT_SUCCESS;
}

int multiply_integer_float(number_t *src_integer, number_t *src_float, answer_t *dst_answer)
{
	//инициализируем ответ исходными данными
	dst_answer->sign = '+';
	for (size_t i = 0; i < M_SIGNIFICANT * 2 + 2; i++)
		dst_answer->significant[i] = 0;
	dst_answer->significant[M_SIGNIFICANT * 2 + 2] = -1;
	dst_answer->exponent = 0;

	//если одно из чисел ноль, то сразу выдаем ответ и выходим
	if (src_integer->significant[0] == 0 || src_float->significant[0] == 0)
	{
		dst_answer->significant[M_SIGNIFICANT * 2] = -1;
		return EXIT_SUCCESS;
	}
	//определяем знак ответа
	if (src_integer->sign != src_float->sign)
		dst_answer->sign = '-';

	//определяем экспоненту
	dst_answer->exponent = src_float->exponent + src_integer->exponent;
	
	//считаем мантиссу
	size_t int_lenght = 0;
	size_t float_lenght = 0;
	for (size_t i = 0; src_integer->significant[i] != -1; i++)
		int_lenght++;
	for (size_t i = 0; src_float->significant[i] != -1; i++)
		float_lenght++;

	int cur_int_digit = 0;
	int cur_float_digit = 0;
	int cur_ans_number = 0;
	int shift = 0;
	int temp_calc = 0;
	for (size_t i = 0; i < int_lenght; i++)
	{
		cur_int_digit = src_integer->significant[int_lenght - i - 1];
		for (size_t j = 0; j < float_lenght; j++)
		{
			cur_float_digit = src_float->significant[float_lenght - j - 1];
			cur_ans_number = dst_answer->significant[M_SIGNIFICANT * 2 - i - j + 1];

			temp_calc = cur_int_digit * cur_float_digit + shift + cur_ans_number;
			dst_answer->significant[M_SIGNIFICANT * 2 - i - j + 1] = temp_calc % 10;
			shift = temp_calc / 10;
		}
			dst_answer->significant[M_SIGNIFICANT * 2 - i - float_lenght + 1] = shift;
		shift = 0;
	}
	dst_answer->significant[M_SIGNIFICANT * 2 - int_lenght - float_lenght + 1] = -1;
 	
	//корректируем мантиссу

	size_t start = 0;
	for (size_t i = 0; dst_answer->significant[i] != -1; i++)
		start++;
	
	for (size_t i = start + 1; dst_answer->significant[i] == 0; i++)
	{
		dst_answer->exponent -= 1;
		dst_answer->significant[i - 1] = 0;
		dst_answer->significant[i] = -1;
	}
	
	for (size_t i = start + 1; dst_answer->significant[i] != -1; i++)
		if (i - start == 30 && dst_answer->significant[i + 1] != -1)
		{
			if (dst_answer->significant[i + 1] >= 5)
				dst_answer->significant[i] += 1;
			dst_answer->significant[i + 1] = -1;

			for (size_t j = i; dst_answer->significant[j] > 9; j--)
			{
				dst_answer->significant[j] %= 10;
				if (dst_answer->significant[j - 1] == -1)
				{
					dst_answer->significant[j - 1] = 1;
					dst_answer->significant[j - 2] = -1;
					start--;
				}
				else
					dst_answer->significant[j - 1] += 1;
			}
		}

	//проверка экспоненты
	for (size_t i = start + 1; dst_answer->significant[i] == 0; i++)
	{
		dst_answer->exponent -= 1;
		dst_answer->significant[i - 1] = 0;
		dst_answer->significant[i] = -1;
	}

	int max_exponent = 9;
	for (size_t i = 1; i < M_EXPONENT; i++)
	{
		max_exponent *= 10;
		max_exponent += 9;
	}
	if (dst_answer->exponent > max_exponent || dst_answer->exponent < -1 * max_exponent)
		return TOO_BIG_EXP;

	return EXIT_SUCCESS; 
}
