#include "../inc/uls.h"

char mx_is_flag_valid(char *flags, const char *valid_flag_list)
{
    do
    {
        if (!mx_is_str_contain((char *)valid_flag_list, *flags))
            return *flags;

    } while (flags++);

    return '\0';
}

bool mx_is_flag_format_valid(char *str)
{
    if (mx_strlen(str) >= 2 && str[0] == '-')
        return true;
    return false;
}
