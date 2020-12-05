#include "../inc/uls.h"

t_dir_info *mx_create_dir_info(char **files, int files_count, bool is_single_files, char *cur_dir_name)
{
    t_dir_info *info = malloc(sizeof(t_dir_info));
    info->files = files;
    info->files_length = files_count;
    info->is_single_files = is_single_files;
    info->cur_dir_name = cur_dir_name;
    return info;
}

t_time *mx_create_time(char *day_of_week, char *month, int day, int hours, int minutes, int seconds, int year)
{
    t_time *time = malloc(sizeof(t_time));
    time->day_of_week = mx_strdup(day_of_week);
    time->month = mx_strdup(month);
    time->day = day;
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
    time->year = year;
    return time;
}
