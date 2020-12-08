#include "../inc/uls.h"

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

void mx_rflag_func(t_dir_info *dir_info)
{
    int j = dir_info->files_length - 1;

    for (int i = 0; i <= j; i++, j--)
    {
        mx_swap(&(dir_info->files[i]), &(dir_info->files[j]));
    }
}

void mx_tflag_func(t_dir_info *dir_info)
{
    mx_sort_str_arr(&(dir_info->files), dir_info->files_length, dir_info->cur_dir_name, &mx_sortf_modt);
}

void mx_Sflag_func(t_dir_info *dir_info)
{
    mx_sort_str_arr(&(dir_info->files), dir_info->files_length, dir_info->cur_dir_name, &mx_sortf_size);
}

void mx_uflag_func(t_dir_info *dir_info)
{
    mx_sort_str_arr(&(dir_info->files), dir_info->files_length, dir_info->cur_dir_name, &mx_sortf_acct);
}

void mx_lflag_func(t_dir_info *dir_info, enum DateTimeMode date_time_mode)
{
    int incr = dir_info->is_single_files ? 0 : 1;

    struct passwd *pw;
    struct group *gr;
    struct stat fileStat;
    t_time *time_mod;

    time_t time_ob;
    time(&time_ob);

    t_time *time_cur = mx_parse_time_str((const char *)ctime(&time_ob));

    char **larr = malloc(sizeof(char *) * (dir_info->files_length + incr));

    // максимальный размер каждого столбца
    int permissions_lm = 10,
        nlink_lm = 0,
        owner_lm = 0,
        group_lm = 0,
        size_lm = 0,
        time_or_year_lm = 0;

    int total_block_size = 0;
    char *cur_name;

    for (int i = 0; i < dir_info->files_length; i++)
    {
        char *tmp = mx_strconcant_new(dir_info->cur_dir_name, "/");
        cur_name = mx_strconcant_new(tmp, dir_info->files[i]);

        int cur_len;

        stat(cur_name, &fileStat);

        total_block_size += (int)(fileStat.st_blocks);

        time_t show_time = date_time_mode == ACCESS_TIME ? fileStat.st_atime : fileStat.st_mtime;
        time_mod = mx_parse_time_str((const char *)ctime(&(show_time)));

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

        free(cur_name);
    }

    if (incr)
    {
        total_block_size /= 2;
        char *total_blocks_str = mx_strnew(5 + mx_strlen(mx_itoa(total_block_size)));

        mx_strcat(total_blocks_str, "total ");
        mx_strcat(total_blocks_str, mx_itoa(total_block_size));
        larr[0] = total_blocks_str;
    }

    for (int i = 0; i < dir_info->files_length; i++)
    {
        char *tmp = mx_strconcant_new(dir_info->cur_dir_name, "/");
        cur_name = mx_strconcant_new(tmp, dir_info->files[i]);

        stat(cur_name, &fileStat);

        pw = getpwuid(fileStat.st_uid);
        gr = getgrgid(fileStat.st_gid);

        time_t show_time = date_time_mode == ACCESS_TIME ? fileStat.st_atime : fileStat.st_mtime;
        time_mod = mx_parse_time_str((const char *)ctime(&(show_time)));

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

        for (int i = 0; i <
                        (time_mod->year == time_cur->year ? (mx_montstr_to_num(time_cur->month) - mx_montstr_to_num(time_mod->month) < 6 ? 1 : 2) : 2);
             i++)
            mx_strcat(cur_file_info, " ");

        if ((time_mod->year == time_cur->year && (mx_montstr_to_num(time_cur->month) - mx_montstr_to_num(time_mod->month) < 6)))
        {
            if (time_mod->hours < 10)
                mx_strcat(cur_file_info, "0");

            mx_strcat(cur_file_info, mx_itoa(time_mod->hours));
            mx_strcat(cur_file_info, ":");

            if (time_mod->minutes < 10)
                mx_strcat(cur_file_info, "0");

            mx_strcat(cur_file_info, mx_itoa(time_mod->minutes));
        }
        else
        {
            mx_strcat(cur_file_info, mx_itoa(time_mod->year));
        }

        mx_strcat(cur_file_info, " ");
        mx_strcat(cur_file_info, dir_info->files[i]);

        larr[i + incr] = cur_file_info;

        free(tmp);
        free(cur_name);
    }

    dir_info->files_length += incr;
    dir_info->files = larr;
}
