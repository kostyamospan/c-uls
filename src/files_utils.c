#include "../inc/uls.h"

t_dir_info *mx_get_files_from_dir(char *dir_path)
{
    DIR *d;
    struct dirent *dir;
    int files_count = 0;

    d = opendir(dir_path);

    while ((dir = readdir(d)) != NULL)
        files_count++;

    closedir(d);

    char **files = malloc(sizeof(char *) * files_count);

    for (int i = 0; i < files_count; i++)
    {
        files[i] = mx_strnew(256);
    }

    d = opendir(dir_path);

    int i = 0;

    while ((dir = readdir(d)) != NULL)
    {
        mx_strcpy(files[i], dir->d_name);
        i++;
    }

    closedir(d);
    mx_sort_str_arr(&files, files_count, dir_path, &mx_sort_asc);
    return mx_create_dir_info(files, files_count, false, dir_path);
}

t_dir_info *mx_process_files_flag(t_dir_info *dir_info, char *flags)
{
    int i;

    if (!dir_info->is_single_files)
    {
        if (mx_str_contains(flags, 'A') == -1 && mx_str_contains(flags, 'a') == -1)
        {
            while ((i = mx_search_hiden_files(dir_info)) > -1)
            {
                mx_string_arr_rm(&(dir_info->files), dir_info->files_length, i);
                if (dir_info->files_length > 0)
                    dir_info->files_length -= 1;
            }
        }
    }

    if (mx_str_contains(flags, 'A') > 0)
    {
        if (mx_str_contains(flags, 'a') == -1)
            mx_Aflag_func(dir_info);
    }
    if (mx_str_contains(flags, 't') > 0)
    {
        mx_tflag_func(dir_info);
    }
    if (mx_str_contains(flags, 'S') > 0)
    {
        mx_Sflag_func(dir_info);
    }
    if (mx_str_contains(flags, 'r') > 0)
    {
        mx_rflag_func(dir_info);
    }
    if (mx_str_contains(flags, 'u') > 0 && mx_str_contains(flags, 'l') == -1)
    {
        mx_uflag_func(dir_info);
    }
    if (mx_str_contains(flags, 'l') > 0)
    {
        if (mx_str_contains(flags, 'u') > 0)
        {
            if (mx_str_contains(flags, 't') > 0)
            {
                mx_uflag_func(dir_info);
            }

            mx_lflag_func(dir_info, ACCESS_TIME);
        }
        else
        {
            mx_lflag_func(dir_info, MODIFICATION_TIME);
        }
    }
    return dir_info;
}
