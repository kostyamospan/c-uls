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
        't',
        'S',
        'u',
    };

    char *flags = NULL;

    char **dir_and_files;
    int dir_and_files_count = 0;

    t_dir_info *dir_info = NULL;

    if (argc >= 2)
    {
        if (mx_is_flag(args[1]))
        {
            flags = mx_strntcpy(flags, args[1], 1, mx_strlen(args[1]));

            char invalid_flag;

            if ((invalid_flag = mx_is_flag_availible(flags, valid_flag_list)) != '\0')
            {
                mx_print_invalid_flag_err(invalid_flag);
                exit(1);
            }
        }

        if (flags == NULL)
        {
            dir_and_files = &(args[1]);
            dir_and_files_count = argc - 1;
        }
        else if (argc >= 3)
        {
            dir_and_files = &(args[2]);
            dir_and_files_count = argc - 2;
        }
    }

    flags = flags == NULL ? "" : flags;

    if (dir_and_files_count >= 1)
    {
        mx_sort_str_arr(&dir_and_files, dir_and_files_count, ".", mx_sort_asc);
        // bool was_error = false;
        int files_count = 0, dirs_count = 0;
        char **files;

        for (int i = 0; i < dir_and_files_count; i++)
        {
            if (mx_is_file(dir_and_files[i]))
            {
                files_count++;
            }
            else if (mx_is_folder(dir_and_files[i]))
            {
                dirs_count++;
            }
            else
            {
                mx_print_invalid_file(dir_and_files[i]);
                if (dir_and_files_count == 1)
                    exit(1);
            }
        }

        files = malloc(files_count * sizeof(char *));
        int j = 0;

        for (int i = 0; i < dir_and_files_count; i++)
        {
            if (mx_is_file(dir_and_files[i]))
            {
                files[j] = mx_strdup(dir_and_files[i]);
                j++;
            }
        }

        dir_info = mx_create_dir_info(files, files_count, true, ".");
        dir_info = mx_process_files_flag(dir_info, flags);

        if (files_count != 0)
        {
            mx_print_files(dir_info, flags);
            if (dirs_count != 0)
                mx_printstr("\n");
        }

        int cur_dir_i = 0;

        for (int i = 0; i < dir_and_files_count; i++)
        {
            if (mx_is_folder(dir_and_files[i]))
            {

                if (files_count != 0 || dirs_count > 1)
                {
                    if (cur_dir_i != 0)
                        mx_printstr("\n");
                    mx_printstr(dir_and_files[i]);
                    mx_printstr(":\n");
                }

                cur_dir_i++;
                dir_info = mx_get_files_from_dir(mx_strdup(dir_and_files[i]));
                dir_info = mx_process_files_flag(dir_info, flags);
                mx_print_files(dir_info, flags);
            }
        }
    }
    else
    {
        dir_info = mx_get_files_from_dir(".");
        dir_info = mx_process_files_flag(dir_info, flags);
        mx_print_files(dir_info, flags);
    }

    if (!dir_info)
        free(dir_info);

    return 0;
}
