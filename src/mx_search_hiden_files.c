#include "../inc/uls.h"

int mx_search_hiden_files(t_dir_info *dir_info)
{
    for (int i = 0; i < dir_info->files_length; i++)
    {
        if (dir_info->files[i][0] == '.')
        {
            return i;
        }
    }
    
    return -1;
}