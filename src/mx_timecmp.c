#include "../inc/uls.h"

int mx_timecmp(t_time *t1, t_time *t2)
{
    if (t1->year > t2->year)
        return -1;
    else if (t1->year < t2->year)
        return 1;
    else
    {
        if (mx_montstr_to_num(t1->month) > mx_montstr_to_num(t2->month))
            return -1;
        else if (mx_montstr_to_num(t1->month) < mx_montstr_to_num(t2->month))
            return 1;
        else
        {
            if (t1->day > t2->day)
                return -1;
            else if (t1->day < t2->day)
                return 1;
            else
            {
                if (t1->hours > t2->hours)
                    return -1;
                else if (t1->hours < t2->hours)
                    return 1;
                else
                {
                    if (t1->minutes > t2->minutes)
                        return -1;
                    else if (t1->minutes < t2->minutes)
                        return 1;
                    else
                    {
                        if (t1->seconds > t2->seconds)
                            return -1;
                        else if (t1->seconds < t2->seconds)
                            return 1;
                        else
                            return 0;
                    }
                }
            }
        }
    }
}
