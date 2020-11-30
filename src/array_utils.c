#include "../inc/uls.h"
#include <string.h>

void mx_string_arr_rm(char ***arr, int size, int index)
{
    char **new_arr = malloc(sizeof(char *) * (size - 1));

    int j = 0;

    for (int i = 0; i < index; i++)
    {
        new_arr[i] = mx_strnew(mx_strlen((*arr)[i]) + 1);
        mx_strcpy(new_arr[i], (*arr)[i]);
        j++;
    }

    for (int i = index + 1; i < size; i++)
    {
        new_arr[j] = mx_strnew(mx_strlen((*arr)[i]) + 1);
        mx_strcpy(new_arr[j], (*arr)[i]);
        j++;
    }

    free(*arr);
    *arr = new_arr;
}
