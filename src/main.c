#include "../inc/uls.h"
#include <dirent.h>
#include <stdio.h>

int main(int argc, char **args)
{
    char *dir_name = ".";
    char *file_name;

    char *flags;

    bool is_folder = false;
    bool is_file = false;

    if (argc == 3)
    {
        if (mx_is_flag_format_valid(args[1]))
        {
            if (mx_is_file(args[1]))
            {
                file_name = args[1];
                is_file = true;
            }
            else if (mx_is_folder(args[1]))
            {
                dir_name = args[1];
                is_folder = true;
            }
            else
            {
                printf("not file or dir");
                exit(1);
            }
        }
    }
    else if (argc == 2)
    {
        if (mx_is_flag_format_valid(args[1]))
        {
        }
        else
        {
            if (mx_is_file(args[1]))
            {
                file_name = args[1];
                is_file = true;
            }
            else if (mx_is_folder(args[1]))
            {
                dir_name = args[1];
                is_folder = true;
            }
        }
    }
    else if (argc != 1)
    {
        return 1;
    }

    if (is_folder)
    {

        DIR *d;
        struct dirent *dir;

        d = opendir(dir_name);

        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
    }
    else
    {
        printf("file work");
    }

    return 0;
}
