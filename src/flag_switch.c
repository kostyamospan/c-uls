#include "../inc/uls.h"

int mx_execute_flag_func(char *flag, const char **flag_list)
{
    int i = 0;

    while (flag_list[i] != null)
    {
        if (mx_strcmp((const char *)flag_list[i], "l"))
        {
            mx_lflag_func();
            return 1;
        }
    }

    return 0;
}
