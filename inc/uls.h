#pragma once

#include "../libmx/inc/libmx.h"
#include <stdbool.h>
#define null ((void *)0)

const char *FLAG_LIST = {
    "l",
    null,
};

bool mx_is_flag_format_valid(char *str);
bool mx_is_flag_valid(char *flags);
void mx_lflag_func();
bool mx_is_file(const char *path);
bool mx_is_folder(const char *path);
