#pragma once

#include "../libmx/inc/libmx.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct s_dir_info
{
    char **files;
    int files_length;
} t_dir_info;

typedef struct s_time
{
    char *day_of_week;
    char *month;
    int day;
    int hours;
    int minutes;
    int seconds;
    int year;
} t_time;

bool mx_is_flag_format_valid(char *str);
char mx_is_flag_valid(char *flags, const char *valid_flag_list);
void mx_lflag_func();
bool mx_is_file(const char *path);
bool mx_is_folder(const char *path);
void mx_print_column(t_dir_info *dir_info);
t_dir_info *mx_get_files_from_dir(char *dir_path);
t_dir_info *mx_process_files_flag(t_dir_info *dir_info, char *flags);
void mx_string_arr_rm(char ***arr, int size, int index);
int mx_search_hiden_files(t_dir_info *dir_info);
int mx_search_string(const char **arr, int arr_size, const char *str);
char *mx_create_space_string(int size);
t_time *mx_parse_time_str(const char *str);


//constructors
t_time *mx_create_time(char *day_of_week, char *month, int day, int hours, int minutes, int seconds, int year);
t_dir_info *mx_create_dir_info(char **files, int files_count);

//flags work
void mx_Aflag_func(t_dir_info *dir_info);
void mx_lflag_func(t_dir_info *dir_info);
void mx_rflag_func(t_dir_info *dir_info);