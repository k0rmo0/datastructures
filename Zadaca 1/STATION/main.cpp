#include "Station.h"
#include <iostream>

int main()
{
    std::vector<std::vector<time>> vec;
    vec = input();
    int temp = 0;
    while (temp != 4)
    {
        temp = menu(vec);
    }
    return 0;
    
}