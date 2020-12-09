#include "../inc/uls.h"

int max_len_names(t_dir_info *dir_info)
{
    int max = 0;
    int temp = 0;

    for (int i = 0; i < dir_info->files_length; i++)
    {
        temp = mx_strlen(dir_info->files[i]);
        if (temp > max)
            max = temp;
    }
    if (max % 8 == 0)
        max += 8;
    else
        max = 8 - (max % 8) + max;
    return max;
}

void mx_print_tab(int len, int maxlen)
{
    int count = 0;
    int p;

    p = maxlen - len;
    if (p % 8 != 0)
        count = (p / 8) + 1;
    else
        count = p / 8;
    for (int i = 0; i < count; i++)
        mx_printchar('\t');
}

void printcols(t_dir_info *dir_info, int rows, int num, int maxlen)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; i + j < num; j += rows)
        {
            mx_printstr(dir_info->files[i + j]);
            if ((i + j + 1) < dir_info->files_length && (i + j + rows < num))
                mx_print_tab(mx_strlen(dir_info->files[i + j]), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}

void print_names(t_dir_info *dir_info, int maxlen, int wincol)
{
    int rows;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = dir_info->files_length;

    if (maxlen * cols > wincol && cols != 1)
        cols--;

    if (num * maxlen > wincol)
    {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
            rows += 1;
        printcols(dir_info, rows, num, maxlen);
    }
    else
        for (int i = 0; i < dir_info->files_length; i++)
        {
            mx_printstr(dir_info->files[i]);
            if ((i + 1) < dir_info->files_length)
                mx_print_tab(mx_strlen(dir_info->files[i]), maxlen);
        }
    mx_printchar('\n');
}

void mx_print_files(t_dir_info *dir_info, char *flags)
{
    int maxlen;
    struct winsize win;

    if (!dir_info)
        return;
    maxlen = max_len_names(dir_info);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

    if (isatty(1))
    {
        if (mx_strlen(flags) >= 1 && mx_str_contains(flags, 'l'))
            mx_print_column(dir_info);
        else
            print_names(dir_info, maxlen, win.ws_col);
    }
    else
        mx_print_column(dir_info);
}

void mx_print_column(t_dir_info *dir_info)
{
    for (int i = 0; i < dir_info->files_length; i++)
    {
        mx_printstr(dir_info->files[i]);
        mx_printstr("\n");
    }
}
