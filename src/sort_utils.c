#include "../inc/uls.h"

void mx_sort_str_arr(char ***arr, int size, bool (*f)(char *, char *))
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (f((*arr)[j], (*arr)[j + 1]))
                mx_swap(&((*arr)[j]), &((*arr)[j + 1]));
}

bool mx_sort_asc(char *a, char *b)
{
    return mx_strcmp(a, b) > 0;
}
