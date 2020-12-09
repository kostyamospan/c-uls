#pragma once

#include "../libmx/inc/libmx.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/ioctl.h>

#define MX_IS_BLK(mode) (((mode)&S_IFMT) == S_IFBLK)
#define MX_IS_CHR(mode) (((mode)&S_IFMT) == S_IFCHR)
#define MX_IS_DIR(mode) (((mode)&S_IFMT) == S_IFDIR)
#define MX_IS_LNK(mode) (((mode)&S_IFMT) == S_IFLNK)
#define MX_IS_SOCK(mode) (((mode)&S_IFMT) == S_IFSOCK)
#define MX_IS_FIFO(mode) (((mode)&S_IFMT) == S_IFIFO)
#define MX_IS_WHT(mode) (((mode)&S_IFMT) == S_IFWHT)
#define MX_IS_REG(mode) (((mode)&S_IFMT) == S_IFREG)
#define MX_IS_EXEC(mode) ((mode)&S_IXUSR)

typedef struct s_dir_info
{
    char **files;
    int files_length;
    bool is_single_files;
    char *cur_dir_name;
} t_dir_info;

enum DateTimeMode
{
    MODIFICATION_TIME,
    CREATION_TIME,
    ACCESS_TIME
};

typedef struct s_time
{
    char *day_of_week;
    char *month;
    int day;
    int hours;
    int minutes;
    int seconds;
    int year;
} t_time;

bool mx_is_flag(char *str);
char mx_is_flag_availible(char *flags, const char *valid_flag_list);
void mx_lflag_func();
void mx_print_column(t_dir_info *dir_info);
t_dir_info *mx_get_files_from_dir(char *dir_path);
t_dir_info *mx_process_files_flag(t_dir_info *dir_info, char *flags);
void mx_string_arr_rm(char ***arr, int size, int index);
int mx_search_hiden_files(t_dir_info *dir_info);
int mx_search_string(const char **arr, int arr_size, const char *str);
t_time *mx_parse_time_str(const char *str);
void mx_swap(void **a, void **b);
int mx_montstr_to_num(const char *str);
char *mx_strconcant_new(const char *str1, const char *str2);

//sort utils
void mx_sort_str_arr(char ***arr, int size, char *dir_name, bool (*f)(char *, char *));
bool mx_sort_asc(char *a, char *b);
bool mx_sort_rev(char *a, char *b);
bool mx_sortf_modt(char *a, char *b);
bool mx_sortf_size(char *a, char *b);
bool mx_sortf_acct(char *a, char *b);
int mx_timecmp(t_time *t1, t_time *t2);

//constructors
t_time *mx_create_time(char *day_of_week, char *month, int day, int hours, int minutes, int seconds, int year);
t_dir_info *mx_create_dir_info(char **files, int files_count, bool is_single_files, char *cur_dir_name);

//flags work
void mx_lflag_func(t_dir_info *dir_info, enum DateTimeMode date_time_mode);
void mx_Aflag_func(t_dir_info *dir_info);
void mx_rflag_func(t_dir_info *dir_info);
void mx_tflag_func(t_dir_info *dir_info);
void mx_Sflag_func(t_dir_info *dir_info);
void mx_uflag_func(t_dir_info *dir_info);

//error utils
void mx_print_invalid_flag_err(char flag);
void mx_print_usage();
void mx_print_invalid_file(char *name);

//obj determination
/* mode_t mx_getstmode(const char *path);
bool mx_is_file(const char *path);
bool mx_is_folder(const char *path);
bool mx_is_slink(const char *path);
bool mx_is_chrdv(const char *path);
bool mx_is_blcdv(const char *path);
bool mx_is_fifo(const char *path);
bool mx_is_sock(const char *path); */
bool mx_is_file(const char *path);
bool mx_is_folder(const char *path);

//спизженный вывод
int max_len_names(t_dir_info *dir_info);
void mx_print_tab(int len, int maxlen);
void printcols(t_dir_info *dir_info, int rows, int num, int maxlen);
void print_names(t_dir_info *dir_info, int maxlen, int wincol);
void mx_print_files(t_dir_info *dir_info, char *flags);
