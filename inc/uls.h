#pragma once

#include "../libmx/inc/libmx.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct s_dir_info
{
    char **files;
    int files_length;
} t_dir_info;

bool mx_is_flag_format_valid(char *str);
bool mx_is_flag_valid(char *flags, const char *flag_list);
void mx_lflag_func();
bool mx_is_file(const char *path);
bool mx_is_folder(const char *path);
void mx_print_column(t_dir_info *dir_info);
t_dir_info *mx_get_files_from_dir(char *dir_path);

t_dir_info *mx_create_dir_info(char **files, int files_count);
