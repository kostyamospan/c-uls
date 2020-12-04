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
    mx_sort_str_arr(&files, files_count, &mx_sort_asc);
    return mx_create_dir_info(files, files_count, false);
}

t_dir_info *mx_process_files_flag(t_dir_info *dir_info, char *flags)
{
    char cur_flag;
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

    i = 0;

    while ((cur_flag = flags[i++]))
    {
        switch (cur_flag)
        {
        case 'a':
            break;
        case 'A':
            mx_Aflag_func(dir_info);
            break;
        case 'r':
            mx_rflag_func(dir_info);
            break;
        case 'l':
            mx_lflag_func(dir_info);
            break;
        default:
            break;
        }
    }

    return dir_info;
}
