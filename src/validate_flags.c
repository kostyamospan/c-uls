#include "../inc/pathfinder.h"

bool mx_is_flag_valid(char *flags)
{
    do
    {
        if (!mx_str_contains((char *)FLAG_LIST, *flags))
            return false;

    } while (flags++);

    return true;
}

bool mx_is_flag_format_valid(char *str)
{
    if (mx_strlen(str) > 2 && str[0] == '-')
        return true;
    return false;
}
