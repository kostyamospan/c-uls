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

void swap(void **a, void **b)
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
        swap(&(dir_info->files[i]), &(dir_info->files[j]));
    }
}

void mx_lflag_func(t_dir_info *dir_info)
{
    char **larr = malloc(sizeof(char *) * dir_info->files_length);

    // максимальный размер каждого столбца
    int permissions_lm = 10,
        nlink_lm = 0,
        owner_lm = 0,
        group_lm = 0,
        size_lm = 0,
        time_lm = 0;

    for (int i = 0; i < dir_info->files_length; i++)
    {
        struct stat fileStat;
        int cur_len;

        if (stat(dir_info->files[i], &fileStat) < 0)
        {
            printf("error\n");
            exit(1);
        }
        else
        {
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group *gr = getgrgid(fileStat.st_gid);

            if ((cur_len = mx_strlen(mx_itoa(fileStat.st_nlink))) > nlink_lm)
                nlink_lm = cur_len;

            if ((cur_len = mx_strlen(pw->pw_name)) > owner_lm)
                owner_lm = cur_len;

            if ((cur_len = mx_strlen(gr->gr_name)) > group_lm)
                group_lm = cur_len;

            if ((cur_len = mx_strlen(mx_itoa(fileStat.st_size))) > size_lm)
                size_lm = cur_len;
        }
    }

    printf("%d, %d, %d, %d\n", nlink_lm, group_lm, owner_lm, size_lm);

    for (int i = 0; i < dir_info->files_length; i++)
    {
        struct stat fileStat;

        if (stat(dir_info->files[i], &fileStat) < 0)
        {
            printf("error\n");
            exit(1);
        }
        else
        {
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group *gr = getgrgid(fileStat.st_gid);

            int cur_str_size = permissions_lm + group_lm + nlink_lm + owner_lm + size_lm + mx_strlen(dir_info->files[i]) + 4;

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

            mx_strcat(cur_file_info, " ");
            // mx_strcat(cur_file_info, mx_create_space_string(nlink_lm - mx_strlen(mx_itoa(fileStat.st_nlink))));
            mx_strcat(cur_file_info, mx_itoa(fileStat.st_nlink));
            mx_strcat(cur_file_info, " ");

            mx_strcat(cur_file_info, pw->pw_name);
            mx_strcat(cur_file_info, " ");

            mx_strcat(cur_file_info, gr->gr_name);
            mx_strcat(cur_file_info, " ");

            // mx_strcat(cur_file_info, mx_create_space_string(size_lm - mx_strlen(mx_itoa(fileStat.st_size))));
            mx_strcat(cur_file_info, mx_itoa(fileStat.st_size));
            // mx_strcat(cur_file_info, " ");
            // mx_strcat(cur_file_info, mx_create_space_string(nlink_lm - mx_strlen(mx_itoa(fileStat.st_nlink))));
            // mx_strcat(cur_file_info, mx_itoa(fileStat.st_atime));
            printf("%s\n", ctime(&(fileStat.st_mtime)));
            t_time *time = mx_parse_time_str((const char *)ctime(&(fileStat.st_mtime)));

            printf("%s %s %d %d:%d:%d %d",
                   time->day_of_week,
                   time->month,
                   time->day,
                   time->hours,
                   time->minutes,
                   time->seconds,
                   time->year);
            // int seconds = time / 60;

            mx_strcat(cur_file_info, " ");
            mx_strcat(cur_file_info, dir_info->files[i]);

            larr[i] = cur_file_info;
        }
    }

    dir_info->files = larr;
}

char *mx_create_space_string(int size)
{
    char *str = mx_strnew(size);
    for (int i = 0; i < size; i++)
    {
        str[i] = ' ';
    }
    return str;
}
