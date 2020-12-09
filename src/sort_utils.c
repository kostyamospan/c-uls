#include "../inc/uls.h"

void mx_sort_str_arr(char ***arr, int size, char *dir_name, bool (*f)(char *, char *))
{
    {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++)
            {
                char *tmp = mx_strconcant_new(mx_strdup(dir_name), "/");
                char *b_path = mx_strconcant_new(tmp, (*arr)[j]);
                char *a_path = mx_strconcant_new(tmp, (*arr)[j + 1]);

                if (!f(a_path, b_path))
                    mx_swap((void**)(&((*arr)[j])), (void**)(&((*arr)[j + 1])));

                free(tmp);
                free(b_path);
                free(a_path);
            }
    }
}

bool mx_sort_asc(char *a, char *b)
{
    return mx_strcmp(a, b) > 0;
}

bool mx_sort_rev(char *a, char *b)
{
    return a > b ? false : false;
}

bool mx_sortf_modt(char *a, char *b)
{
    struct stat a_st;
    struct stat b_st;

    stat(a, &a_st);
    stat(b, &b_st);

    t_time *t1 = mx_parse_time_str(ctime(&(a_st.st_mtime)));
    t_time *t2 = mx_parse_time_str(ctime(&(b_st.st_mtime)));

    int res = mx_timecmp(t1, t2);

    free(t1);
    free(t2);

    return res > 0;
}

bool mx_sortf_size(char *a, char *b)
{
    struct stat a_st;
    struct stat b_st;

    stat(a, &a_st);
    stat(b, &b_st);

    return a_st.st_size < b_st.st_size;
}

bool mx_sortf_acct(char *a, char *b)
{
    struct stat a_st;
    struct stat b_st;

    stat(a, &a_st);
    stat(b, &b_st);

    t_time *t1 = mx_parse_time_str(ctime(&(a_st.st_atime)));
    t_time *t2 = mx_parse_time_str(ctime(&(b_st.st_atime)));

    int res = mx_timecmp(t1, t2);

    free(t1);
    free(t2);

    return res > 0;
}

void mx_swap(void **a, void **b)
{
    void *c = *a;
    *a = *b;
    *b = c;
}
