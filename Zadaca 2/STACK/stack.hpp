#ifndef _STACK_
#define _STACK_
#include<iostream>
#include<utility>


template<typename T>
class Node
{
    public:
    T value;
    Node<T>* next_;
    template<typename U>
    Node(U&& val) : value{std::forward<U>(val)}, next_{nullptr} {}
};

template<typename T>
class Stack
{
    public:
    Stack();
    ~Stack();
    Stack (const Stack<T>& other);
    Stack (Stack<T>&& other);
    Stack& operator=(const Stack<T>& other);
    Stack& operator=(Stack<T>&& other);
    template<typename U>
    void push(U&& item);
    void pop();
    T top() const;
    size_t size() const;
    bool empty() const;

    private:
    Node<T>* head_;
    size_t size_;

    void deleteStack()
    {
        while(head_ != nullptr)
        {
            auto temp = head_;
            head_ = head_ -> next_;
            delete temp;
        }
    }

    void copyStack (const Stack<T>& other)
    {
        head_ = new Node<T>(other.head_ -> value);
        auto temp = other.head_ -> next_;
        auto temp2 = head_;
        size_ = other.size_;

        for(auto i = 1 ; i < other.size_; ++i)
        {
            temp2 = temp2 -> next_ = new Node<T> (temp -> value);
            temp = temp -> next_;
        }
    }
};

template<typename T>
Stack<T>::Stack() : head_{nullptr}, size_{0} {}

template<typename T>
Stack<T>::~Stack()
{
    deleteStack();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
    copyStack(other);
}

template<typename T>
Stack<T>::Stack(Stack<T>&& other) : head_{other.head_}, size_{other.size_}
{
    other.head_ = nullptr;
}

template<typename T>
Stack<T>& Stack<T>:: operator=(const Stack<T>& other)
{
    if (this == &other)
        return *this;
    if (head_ != nullptr)
        deleteStack();

    copyStack(other);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other)
{
    head_ = other.head_;
    size_ = other.size;
    other.head_ = nullptr;
    other.size_ = 0;
}

template<typename T>
template<typename U>
void Stack<T>::push (U&& item)
{
    auto newElement = new Node<T>(std::forward<U>(item));
    newElement -> next_ = head_;
    head_ = newElement;
    size_ ++;
}

template<typename T>
void Stack<T>::pop()
{
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
    size_ --;
}

template<typename T>
T Stack<T>::top() const
{
    return head_ -> value;
}

template<typename T>
size_t Stack<T>::size () const
{
    return size_;
}

template<typename T>
bool Stack<T>::empty () const
{
    return size_ == 0;
}

#endif