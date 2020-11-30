#include "../inc/uls.h"
#include <dirent.h>
#include <stdio.h>

int main(int argc, char **args)
{
    const char valid_flag_list[] = {
        'l',
        'a',
        'A',
        'R',
        'r',
    };

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
            char invalid_flag;

            if ((invalid_flag = mx_is_flag_valid(flags, valid_flag_list)) != '\0')
            {
                printf("Flag %c is invalid\n", invalid_flag);
                exit(0);
            }

            if (mx_is_file(args[2]))
            {
                file_name = args[2];
                is_file = true;
                is_folder = false;
            }
            else if (mx_is_folder(args[2]))
            {
                dir_name = args[2];
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

            char invalid_flag;

            if ((invalid_flag = mx_is_flag_valid(flags, valid_flag_list)) != '\0')
            {
                printf("Flag %c is invalid\n", invalid_flag);
                exit(0);
            }
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
            dir_info = mx_process_files_flag(dir_info, flags);
            mx_print_column(dir_info);
        }
    }

    return 0;
}
