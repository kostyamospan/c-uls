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

    char *flags = NULL;

    char **dir_and_files;
    int dir_and_files_count = 0;

    if (argc >= 2)
    {
        if (mx_is_flag(args[1]))
        {
            flags = mx_strntcpy(flags, args[1], 1, mx_strlen(args[1]));

            char invalid_flag;

            if ((invalid_flag = mx_is_flag_availible(flags, valid_flag_list)) != '\0')
            {
                mx_print_invalid_flag_err(invalid_flag);
                exit(0);
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
        bool was_error = false;
        t_dir_info *dir_info;
        int files_count = 0;
        char **files;

        for (int i = 0; i < dir_and_files_count; i++)
        {
            if (mx_is_file(mx_strdup(dir_and_files[i])))
            {
                files_count++;
            }
            else if (!mx_is_folder(mx_strdup(dir_and_files[i])))
            {
                mx_print_invalid_file(dir_and_files[i]);
            }
        }

        files = malloc(files_count * sizeof(char *));
        int j = 0;

        for (int i = 0; i < dir_and_files_count; i++)
        {
            if (mx_is_file(mx_strdup(dir_and_files[i])))
            {
                files[j] = mx_strdup(dir_and_files[i]);
                j++;
            }
        }
        /*         if (was_error && )
        {
        }
 */
        dir_info = mx_create_dir_info(files, files_count, true);
        dir_info = mx_process_files_flag(dir_info, flags);
        mx_print_column(dir_info);

        for (int i = 0; i < dir_and_files_count; i++)
        {
            if (mx_is_folder(mx_strdup(dir_and_files[i])))
            {
                printf("\n%s:\n", dir_and_files[i]);

                dir_info = mx_get_files_from_dir(mx_strdup(dir_and_files[i]));
                dir_info = mx_process_files_flag(dir_info, flags);
                mx_print_column(dir_info);

                /* if (dir_and_files_count - i != 1)
                    printf("\n"); */
            }
        }
    }
    else
    {
        t_dir_info *dir_info;
        dir_info = mx_get_files_from_dir(".");
        dir_info = mx_process_files_flag(dir_info, flags);
        mx_print_column(dir_info);
    }

    return 0;
}
