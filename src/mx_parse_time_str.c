#include "../inc/uls.h"

t_time *mx_parse_time_str(const char *str)
{
    char **splitted_str = mx_strsplit(str, " ");
    char **splitted_time = mx_strsplit(splitted_str[3], ":");

    t_time *time = mx_create_time(splitted_str[0],
                                  splitted_str[1],
                                  mx_atoi_positive(splitted_str[2]),
                                  mx_atoi_positive(splitted_time[0]),
                                  mx_atoi_positive(splitted_time[1]),
                                  mx_atoi_positive(splitted_time[2]),
                                  mx_atoi_positive(splitted_str[4]));

    /* for (int i = 0; splitted_str[i] != NULL; i++)
    {
        printf("%s ", splitted_str[i]);
    }
    printf("\n"); */
    free(splitted_str);
    free(splitted_time);

    return time;
}