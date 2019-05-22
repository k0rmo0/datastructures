#include<iostream>
#include"queuelink.hpp"


int main()
{
    linkedQueue<int> kju;
    int x;

    while (x)
    {
        std::cin >> x;
        kju.enqueue(x);
        std::cout << std::endl;
    }

    while(!(kju.empty()))
    {
        std::cout << kju.element_ << std::endl;
        kju.dequeue();
    }

    std::cout << "Prvi u redu: " << kju.front() << "Velicina: " << kju.size() << std::endl;
    


    
    

}