#include "../inc/uls.h"

bool mx_is_flag_valid(char *flags, const char *flag_list)
{
    do
    {
        if (!mx_is_str_contain((char *)flag_list, *flags))
            return false;

    } while (flags++);

    return true;
}

bool mx_is_flag_format_valid(char *str)
{
    printf("%d\n", mx_strlen(str));
    if (mx_strlen(str) >= 2 && str[0] == '-')
        return true;
    return false;
}
