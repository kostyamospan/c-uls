#include "../inc/uls.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool mx_is_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode) >= 1 ? true : false;
}

bool mx_is_folder(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode) >= 1 ? true : false;
}
