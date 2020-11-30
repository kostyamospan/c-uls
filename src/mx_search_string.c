#include "../inc/uls.h"

int mx_search_string(const char **arr, int arr_size, const char *str)
{
    for (int i = 0; i < arr_size; i++)
    {
        if (mx_strcmp((const char *)arr[i], (const char *)str) == 0)
            return i;
    }
    return -1;
}
