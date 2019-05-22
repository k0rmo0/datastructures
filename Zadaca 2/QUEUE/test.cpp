#include<iostream>
#include "queue.hpp"



int main ()
{
    queue<int> kju (10);

    int i;

    for (int c = 0; c < 5; ++c)
    {
        std::cin >> i;
        kju.enqueue(i);
    }

    kju.dequeue();
    kju.dequeue();

    std::cout << "SIZE: " << kju.size() << " FIRST ELEMENT: " << kju.front() << std::endl;

    if(!kju.empty())
    {
        std::cout << "Queue is not empty !" << std::endl;
    }

}
