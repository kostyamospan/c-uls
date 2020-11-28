#include "../inc/uls.h"

t_dir_info *mx_create_dir_info(char **files, int files_count)
{
    t_dir_info *info = malloc(sizeof(t_dir_info));
    info->files = files;
    info->files_length = files_count;
    return info;
}
