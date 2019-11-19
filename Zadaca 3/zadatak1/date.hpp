#ifndef _DATE_
#define _DATE_
#include<iostream>

struct date
{
    int day;
    int month;
    int year;
    friend std::ostream& operator<<(std::ostream& out, const date& dt);
};

std::ostream& operator<<(std::ostream& out, const date& dt)
{
    out << dt.day << "." << dt.month << "." << dt.year <<".g ";
    return out;
}

#endif