#include<iostream>
#include "BSTtest.hpp"


int main()
{
    BST<int,int> stablo;

    stablo.insert(10,3);
    stablo.insert(5,4);
    stablo.insert(4,2);
    stablo.insert(12,6);
    stablo.insert(14,5);

    stablo.print_inorder();
    std::cout << std::endl;
    stablo.print_postorder();
    std::cout << std::endl;
    stablo.print_preorder();
    std::cout << std::endl;

    BST<int, int> stablo2;

    stablo2 = stablo;

    stablo2.print_inorder();
    std::cout << std::endl;
    stablo2.print_postorder();
    std::cout << std::endl;
    stablo2.print_preorder();
    std::cout << std::endl;

}
