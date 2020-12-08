#include "../inc/uls.h"

bool mx_is_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode) ? true : false;
}

bool mx_is_folder(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode) ? true : false;
}

// mode_t mx_getstmode(const char *path)
// {
//     char *tmp;
//     struct stat path_stat;
//     stat(mx_strdup(path), &path_stat);
//     return path_stat.st_mode;
// }

// bool mx_is_file(const char *path)
// {
//     return S_ISREG(mx_getstmode(path)) ? true : false;
// }

// bool mx_is_folder(const char *path)
// {
//     return mx_getstmode(path) == __S_IFDIR ? true : false;
// }

// bool mx_is_slink(const char *path)
// {
//     return mx_getstmode(path) == __S_IFLNK ? true : false;
// }

// bool mx_is_chrdv(const char *path)
// {
//     return mx_getstmode(path) == __S_IFCHR ? true : false;
// }

// bool mx_is_blcdv(const char *path)
// {
//     return mx_getstmode(path) == __S_IFBLK ? true : false;
// }

// bool mx_is_fifo(const char *path)
// {
//     return mx_getstmode(path) == __S_IFIFO ? true : false;
// }

// bool mx_is_sock(const char *path)
// {
//     return mx_getstmode(path) == __S_IFSOCK ? true : false;
// }

// // #define __S_IFDIR 0040000  /* Directory.  */
// // #define __S_IFCHR 0020000  /* Character device.  */
// // #define __S_IFBLK 0060000  /* Block device.  */
// // #define __S_IFREG 0100000  /* Regular file.  */
// // #define __S_IFIFO 0010000  /* FIFO.  */
// // #define __S_IFLNK 0120000  /* Symbolic link.  */
// // #define __S_IFSOCK 0140000 /* Socket.  */