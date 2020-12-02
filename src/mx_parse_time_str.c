#include "../inc/uls.h"

//str format is: DayOfWeek Month Day H:M:S Year
t_time *mx_parse_time_str(const char *str)
{
    char **splitted_str = mx_strsplit(str, " ");
    char **splitted_time;

    int incr = 0;

    char *day;

    if (mx_strcmp(splitted_str[2], "") == 0)
    {
        day = splitted_str[3];
        incr = 1;
    }
    else
    {
        day = splitted_str[2];
    }

    splitted_time = mx_strsplit(splitted_str[3 + incr], ":");

    t_time *time = mx_create_time(splitted_str[0],
                                  splitted_str[1],
                                  mx_atoi_positive(day),
                                  mx_atoi_positive(splitted_time[0]),
                                  mx_atoi_positive(splitted_time[1]),
                                  mx_atoi_positive(splitted_time[2]),
                                  mx_atoi_positive(splitted_str[4 + incr]));
    free(splitted_str);
    free(splitted_time);

    return time;
}
