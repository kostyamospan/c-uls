#include "../inc/uls.h"
#include <dirent.h>
#include <stdio.h>

int main(int argc, char **args)
{
    const char *valid_flag_list = {"l"};

    char *dir_name = ".";
    char *file_name;

    char *flags;

    bool is_folder = true;
    bool is_file = false;

    if (argc == 3)
    {
        if (mx_is_flag_format_valid(args[1]))
        {
            flags = mx_strntcpy(flags, args[1], 1, mx_strlen(args[1]));

            printf("%s\n", flags);

            if (mx_is_file(args[1]))
            {
                file_name = args[1];
                is_file = true;
                is_folder = false;
            }
            else if (mx_is_folder(args[1]))
            {
                dir_name = args[1];
            }
            else
            {
                printf("not file or dir\n");
                exit(1);
            }
        }
    }
    else if (argc == 2)
    {
        if (mx_is_flag_format_valid(args[1]))
        {
            flags = mx_strntcpy(flags, args[1], 1, mx_strlen(args[1]));
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
        printf("argc = 1\n");

        return 1;
    }

    printf("%s\n", flags);

    if (is_file)
    {
        printf("file work\n");
    }
    else
    {
        if (mx_is_str_contain(flags, 'R'))
        {
            printf("R flag\n");
        }
        else
        {
            t_dir_info *dir_info = mx_get_files_from_dir(dir_name);
            mx_print_column(dir_info);
        }
    }

    return 0;
}
