#include "../inc/uls.h"

void mx_print_column(t_dir_info *dir_info)
{
    for (int i = 0; i < dir_info->files_length; i++)
    {
        printf("%s\n", dir_info->files[i]);
        // mx_printchar('\n');
    }
}
