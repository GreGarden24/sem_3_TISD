#include "print.h"

#include <stdio.h>

void print_info(void)
{
    printf("\n\nДанная программа проверяет граф на связность\n\n");
}

void print_menu(void)
{
    printf("\
Меню:\n\
1 - Ввести матрицу смежности\n\
2 - Вывести матрицу смежности\n\
3 - Вывести граф\n\
4 - Определить тип графа\n\
5 - Вывод меню\n\n\
0 - Завершить программу\n\n");
}

void print_note(void)
{
    printf("INFO: Чтобы вывести меню, введите - 5\n");
}
