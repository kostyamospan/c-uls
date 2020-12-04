#include "../inc/uls.h"

int mx_montstr_to_num(const char *str)
{
    if (!mx_strcmp(str, "Jan"))
        return 1;
    else if (!mx_strcmp(str, "Jan"))
        return 2;
    else if (!mx_strcmp(str, "Feb"))
        return 3;
    else if (!mx_strcmp(str, "Mar"))
        return 4;
    else if (!mx_strcmp(str, "Apr"))
        return 5;
    else if (!mx_strcmp(str, "May"))
        return 6;
    else if (!mx_strcmp(str, "Jun"))
        return 7;
    else if (!mx_strcmp(str, "Jul"))
        return 8;
    else if (!mx_strcmp(str, "Aug"))
        return 9;
    else if (!mx_strcmp(str, "Sep"))
        return 10;
    else if (!mx_strcmp(str, "Nov"))
        return 11;
    else if (!mx_strcmp(str, "Dec"))
        return 12;
    else
        return -1;
}