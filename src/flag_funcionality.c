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

void mx_lflag_show_func(char **file_list)
{
    printf("---> l flag pseudo work <---");
}

char **mx_aflag_func(char **file_list)
{
    return NULL;
    // printf("---> a flag pseudo work <---");
}
