#include "../inc/uls.h"

int mx_strlen_space(char *str)
{
    int size;

    while (str[size] != '\0' && !mx_isspace(str[size]))
        size++;

    return size;
}
