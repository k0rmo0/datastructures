#include<iostream>
#include<functional>
#include "doubly.h"

int generateId()
{
    static int counter = 0;
    return ++counter;
}

int main ()
{
    int option;
    ToDo task;
    doublyList<ToDo> tasks;

do
{
    
    std::cout << "---------- MENI ----------" << std::endl
    << "Odaberite opciju koju zelite: " << std::endl;
    std::cout <<"1. Unos novih obaveza " << std::endl
    << "2. Prikaz trenutnih obaveza " << std::endl
    << "3. Oznaciti obavezu kako zavrsenu " << std::endl
    << "4. Izaci iz notesa " << std::endl;
    std::cout <<"-------------------------" << std::endl;

    std::cin >> option;
    
    switch (option)
    {
    case 1:
        {std::cout << "Unesite naslov, opis i prioritet obaveze: " <<std::endl;
        std::cout << "Note: 1 najveci prioritet, 5 najmanji prioritet ! " << std::endl;
        std::cin >> task.title >> task.description >> task.priority;
        task.id = generateId();
        tasks.add(task);
        std::cout << "Unjeli ste obavezu ! " << std::endl;
        std::cout<<"-------------------------" << std::endl;
        break;}
    case 2:
        {std::cout << "Trenutne obaveze: " << std::endl << std::endl;
        tasks.print();
        break;}

    case 3:
       { 
        int g;
        std::cout << "Unesite id obaveze koju zelite oznaciti kao dovrsenu : ";
        std::cin >> g;
        std::cout << std::endl;
        auto found = [g] (ToDo id) {return id == g;};
        auto item = tasks.find(found);
        if(item != nullptr)
            { tasks.remove(item);
              std::cout << "Obaveza sa id-om:" << g << "oznacena kao dovrsena ! " << std::endl;
            }
        else
        {
             std::cout << "Nema obaveze sa tim id-om ! " <<std::endl;
             break;
        }
        break;
        }
    case 4:
    break;
    default:
    std::cout << "Niste unjeli validnu vrijednost !" << std::endl;
        break;
    }
}
    while(option != 4);

}