#include "../inc/uls.h"

void mx_print_invalid_flag_err(char flag)
{
    mx_printerr("uls: illegal option -- ");
    write(2, &flag, 1);
    mx_printerr("\n");
    mx_print_usage();
}

void mx_print_usage()
{
    mx_printerr("usage: uls [-l] [file ...]\n");
}

void mx_print_invalid_file(char *name)
{
    mx_printerr("uls: ");
    mx_printerr(name);
    mx_printerr(": No such file or directory\n");
}
