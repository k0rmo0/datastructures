#ifndef _TODO_
#define _TODO_
#include<string>
#include<iostream>

struct ToDo
{
    bool operator<(ToDo a);
    bool operator==(int a) const;
    bool operator>=(ToDo a);
    
    friend std::ostream& operator<<(std::ostream& os, const ToDo& td);
    int id;
    std::string title;
    std::string description;
    int priority;
};

bool ToDo::operator<(ToDo a)
{
    return priority < a.priority;
}

std::ostream& operator<<(std::ostream& os, const ToDo& td)
{
    os << td.id << "   " << td.title << "  " << td.description <<"   "<< td.priority;
    return os;
}

bool ToDo::operator==(int a) const
{
    return id == a;
}

bool ToDo::operator>=(ToDo a) 
{
    return priority >= a.priority;
}

#endif