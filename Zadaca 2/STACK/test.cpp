#include<iostream>
#include "stack.hpp"


using namespace std;

int main()
{
    Stack<int> moj;
    Stack<int> moj2;

    moj.push(3);
    moj.push(2);
    moj.push(4);
    moj.push(12);
    

    while(!moj.empty())
    {
        cout << moj.top() << endl;
        moj.pop();
    }

    moj.push(3);
    moj.push(2);
    moj.push(4);
    moj.push(12);


    moj2 = moj;

     while(!moj2.empty())
    {
        cout << moj2.top() << endl;
        moj2.pop();
    }
    return 0;
}