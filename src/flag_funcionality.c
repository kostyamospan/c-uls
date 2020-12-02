#include "../inc/uls.h"
#include <stdio.h>
#include <dirent.h>

t_dir_info *mx_get_files_from_dir(char *dir_path)
{
    DIR *d;
    struct dirent *dir;
    int files_count = 0;

    d = opendir(dir_path);

    while ((dir = readdir(d)) != NULL)
        files_count++;

    closedir(d);

    char **files = malloc(sizeof(char *) * files_count);

    for (int i = 0; i < files_count; i++)
    {
        files[i] = mx_strnew(256);
    }

    d = opendir(dir_path);

    int i = 0;

    while ((dir = readdir(d)) != NULL)
    {
        mx_strcpy(files[i], dir->d_name);
        i++;
    }

    closedir(d);
    mx_sort_str_arr(&files, files_count, &mx_sort_asc);
    return mx_create_dir_info(files, files_count);
}

t_dir_info *mx_process_files_flag(t_dir_info *dir_info, char *flags)
{
    char cur_flag;
    int i;

    if (mx_str_contains(flags, 'A') == -1 && mx_str_contains(flags, 'a') == -1)
    {
        while ((i = mx_search_hiden_files(dir_info)) > -1)
        {
            mx_string_arr_rm(&(dir_info->files), dir_info->files_length, i);
            if (dir_info->files_length > 0)
                dir_info->files_length -= 1;
        }
    }

    i = 0;

    while ((cur_flag = flags[i++]))
    {
        switch (cur_flag)
        {
        case 'a':
            break;
        case 'A':
            mx_Aflag_func(dir_info);
            break;
        case 'r':
            mx_rflag_func(dir_info);
            break;
        case 'l':
            mx_lflag_func(dir_info);
            break;
        default:
            break;
        }
    }

    return dir_info;
}

void mx_lflag_show_func(char **file_list)
{
    printf("---> l flag pseudo work <---");
}

void mx_Aflag_func(t_dir_info *dir_info)
{
    int index = mx_search_string((const char **)dir_info->files, dir_info->files_length, ".");

    if (index > -1)
    {
        mx_string_arr_rm(&(dir_info->files), dir_info->files_length, index);
        if (dir_info->files_length > 0)
            dir_info->files_length -= 1;
    }

    index = mx_search_string((const char **)dir_info->files, dir_info->files_length, "..");

    if (index > -1)
    {
        mx_string_arr_rm(&(dir_info->files), dir_info->files_length, index);
        if (dir_info->files_length > 0)
            dir_info->files_length -= 1;
    }
}

void mx_swap(void **a, void **b)
{
    void *c = *a;
    *a = *b;
    *b = c;
}

void mx_rflag_func(t_dir_info *dir_info)
{
    int j = dir_info->files_length - 1;

    for (int i = 0; i <= j; i++, j--)
    {
        mx_swap(&(dir_info->files[i]), &(dir_info->files[j]));
    }
}

void mx_lflag_func(t_dir_info *dir_info)
{
    struct passwd *pw;
    struct group *gr;
    struct stat fileStat;
    t_time *time_mod;

    time_t time_ob;
    time(&time_ob);

    t_time *time_cur = mx_parse_time_str((const char *)ctime(&time_ob));

    char **larr = malloc(sizeof(char *) * (dir_info->files_length + 0));

    // максимальный размер каждого столбца
    int permissions_lm = 10,
        nlink_lm = 0,
        owner_lm = 0,
        group_lm = 0,
        size_lm = 0,
        time_or_year_lm = 0;

    int total_block_size = 0;

    for (int i = 0; i < dir_info->files_length; i++)
    {

        int cur_len;

        if (stat(dir_info->files[i], &fileStat) < 0)
        {
            printf("error\n");
            exit(1);
        }
        else
        {
            // total_block_size += (int)(fileStat.st_blksize);

            time_mod = mx_parse_time_str((const char *)ctime(&(fileStat.st_mtime)));

            pw = getpwuid(fileStat.st_uid);
            gr = getgrgid(fileStat.st_gid);

            if ((cur_len = mx_strlen(mx_itoa(fileStat.st_nlink))) > nlink_lm)
                nlink_lm = cur_len;

            if ((cur_len = mx_strlen(pw->pw_name)) > owner_lm)
                owner_lm = cur_len;

            if ((cur_len = mx_strlen(gr->gr_name)) > group_lm)
                group_lm = cur_len;

            if ((cur_len = mx_strlen(mx_itoa(fileStat.st_size))) > size_lm)
                size_lm = cur_len;

            time_or_year_lm = time_mod->day == time_cur->day ? 5 : 4;
        }
    }
    /*  char *total_blocks_str = mx_strnew(5 + mx_strlen(mx_itoa(total_block_size)));

    mx_strcat(total_blocks_str, "total ");
    mx_strcat(total_blocks_str, mx_itoa(total_block_size));
 
    larr[0] = total_blocks_str;*/

    for (int i = 0; i < dir_info->files_length; i++)
    {
        if (stat(dir_info->files[i], &fileStat) < 0)
        {
            printf("error\n");
            exit(1);
        }
        else
        {
            pw = getpwuid(fileStat.st_uid);
            gr = getgrgid(fileStat.st_gid);
            time_mod = mx_parse_time_str((const char *)ctime(&(fileStat.st_mtime)));

            char *nlink_str = mx_itoa((int)fileStat.st_nlink);
            char *file_size_str = mx_itoa((int)fileStat.st_size);

            int cur_str_size = permissions_lm + nlink_lm + owner_lm + group_lm + size_lm + 3 + 2 + time_or_year_lm + mx_strlen(dir_info->files[i]) + 8;

            char *cur_file_info = mx_strnew(cur_str_size);
            mx_strcat(cur_file_info, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IROTH) ? "r" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            mx_strcat(cur_file_info, (fileStat.st_mode & S_IXOTH) ? "x" : "-");

            for (int i = 0; i <= nlink_lm - mx_strlen(nlink_str); i++)
                mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, nlink_str);

            for (int i = 0; i <= owner_lm - mx_strlen(pw->pw_name); i++)
                mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, pw->pw_name);

            for (int i = 0; i <= group_lm - mx_strlen(gr->gr_name); i++)
                mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, gr->gr_name);

            for (int i = 0; i <= size_lm - mx_strlen(file_size_str); i++)
                mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, file_size_str);

            mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, time_mod->month);

            for (int i = 0; i < (time_mod->day < 10 ? 2 : 1); i++)
                mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, mx_itoa(time_mod->day));

            for (int i = 0; i < (time_mod->day == time_cur->day ? 1 : 2); i++)
                mx_strcat(cur_file_info, " ");

            if (time_mod->day == time_cur->day)
            {
                mx_strcat(cur_file_info, mx_itoa(time_mod->hours));
                mx_strcat(cur_file_info, ":");
                mx_strcat(cur_file_info, mx_itoa(time_mod->minutes));
            }
            else
            {
                mx_strcat(cur_file_info, mx_itoa(time_mod->year));
            }

            mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, dir_info->files[i]);

            larr[i] = cur_file_info;
        }
    }

    dir_info->files = larr;
}
