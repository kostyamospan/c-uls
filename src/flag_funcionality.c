#include "../inc/uls.h"
#include <stdio.h>
#include <dirent.h>

t_dir_info *mx_get_files_from_dir(char *dir_path)
{
    DIR *d;
    struct dirent *dir;
    int files_count = 0;

    d = opendir(dir_path);

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
            files_count++;

        closedir(d);
    }
    char **files = malloc(sizeof(char *) * files_count);

    for (int i = 0; i < files_count; i++)
    {
        files[i] = malloc(sizeof(char));
    }

    d = opendir(dir_path);

    if (d)
    {
        for (int i = 0; (dir = readdir(d)) != NULL; i++)
        {
            files[i] = dir->d_name;
        }

        closedir(d);
    }

    return mx_create_dir_info(files, files_count);
}

t_dir_info *mx_process_files_flag(t_dir_info *dir_info, char *flags)
{
    char cur_flag;
    int i;

    if (mx_str_contains(flags, 'A') == -1 && mx_str_contains(flags, 'a') == -1)
    {
        while ((i = mx_search_hiden_files(dir_info)) > -1)
        {
            //printf("", i);
            /* for (int j = 0; j < dir_info->files_length; j++)
            {
                printf("%s ", dir_info->files[j]);
            }
            printf("size = %d\n", dir_info->files_length); */

            dir_info->files = mx_string_arr_rm(dir_info->files, dir_info->files_length, i);
            dir_info->files_length -= 1;

            /*   for (int j = 0; j < dir_info->files_length; j++)
            {
                printf("%s ", dir_info->files[j]);
            }
            
            printf("\n"); */
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
            break;
        default:
            break;
        }
    }

    return dir_info;
}

void mx_lflag_show_func(char **file_list)
{
    printf("---> l flag pseudo work <---");
}

char **mx_aflag_func(char **file_list)
{
    return NULL;
    // printf("---> a flag pseudo work <---");
}
