#include<iostream>
#include"dequeue.hpp"


int main()
{
    DEqueue<int> kju;

    kju.push_back(2);
    kju.push_back(5);
    kju.push_front(12);
    kju.push_front(10);

    kju.pop_back();
    kju.pop_front();

    std::cout << "Prednji element: " << kju.front() << " Zadnji element: " << kju.back() << " Velicina: " << kju.size() << std::endl;

}