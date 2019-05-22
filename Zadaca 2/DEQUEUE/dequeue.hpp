#ifndef _DEQUEUE_
#define _DEQUEUE_
#include<iostream>

template<typename T>
class Node
{
    public:
    Node<T>* next_;
    Node<T>* previous_;
    T element_;
    Node(const T& el = T{}) : element_{el}, previous_{nullptr}, next_{nullptr} {}
};


template<typename T>
class DEqueue
{
    public:
    DEqueue();
    DEqueue(const DEqueue<T>& other);
    ~DEqueue();
    DEqueue(DEqueue <T>&& other);
    DEqueue<T> operator=(const DEqueue<T>& other);
    DEqueue<T> operator=(DEqueue<T>&& other);
    void push_front(const T& item);
    void push_back(const T& item);
    void pop_front();
    void pop_back();
    T& front() const;
    T& back() const;
    size_t size() const;
    bool empty() const;

    private:

    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

    void copy (const DEqueue<T>& other)
    {

        head_ = new Node<T>(other.head_ -> element_);
        tail_ = head_;
        auto temp = other.head_ -> next_;

        for (int i = 1; i < other.size_; ++i)
        {
            tail_ = tail_ -> next_ = new Node<T>(temp -> element_,tail_);
            temp = temp -> next_;
        }
    }

    void deleteQueue()
    {
        auto temp = head_;
        head_ = head_ -> next_;
        delete temp;
    }
};

template<typename T>
DEqueue<T>::DEqueue() : head_{nullptr}, tail_{nullptr}, size_{0} {}

template<typename T>
DEqueue<T>::DEqueue(const DEqueue<T>& other)
{
    if(other.size_ == 0)
    {
        head_ = tail_ = nullptr;
    }
    else
    {
        copy(other);
    }
}

template<typename T>
DEqueue<T>::DEqueue(DEqueue<T>&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_}
{
    head_ = tail_ = nullptr;
}

template<typename T>
DEqueue<T> DEqueue<T>::operator=(const DEqueue<T>& other)
{
    if (this == &other)
        return *this;
    if(size_ == 0)
        deleteQueue();
    
    copy(other);
    size_ = other.size_;
    return *this;
}

template<typename T>
DEqueue<T> DEqueue<T>::operator=(DEqueue<T>&& other) 
{
    size_ = other.size_;
    deleteQueue();
    head_ = other.head_;
    tail_ = other.tail_;
    other.head_ = other.tail_ = nullptr;
    return *this;
}

template<typename T>
DEqueue<T>::~DEqueue()
{
    deleteQueue();
}

template<typename T>
void DEqueue<T>::push_front (const T& item)
{
    if(head_ == nullptr)
    {
        head_ = new Node<T>(item);
        tail_ = head_;
        size_ ++;
    }
    else{
    auto temp = head_;
    head_ = new Node<T>(item);
    head_ -> next_ = temp;
    temp -> previous_ = head_;
    size_ ++;
    }
}

template<typename T>
void DEqueue<T>::push_back (const T& item)
{
    if(head_ == nullptr)
    {
        head_ = new Node<T> (item);
        tail_ = head_;
        size_ ++;
    }
    else
    {
        auto temp = tail_;
        tail_ = new Node<T>(item);
        tail_ -> previous_ = temp;
        temp -> next_ = tail_;
        size_ ++;
    }
}

template<typename T>
void DEqueue<T>::pop_back()
{
    auto temp = tail_;
    tail_ = tail_ -> previous_;
    delete temp;
    size_ --;
}

template<typename T>
void DEqueue<T>::pop_front()
{
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
    size_ --;
}

template<typename T>
size_t DEqueue<T>::size() const 
{
    return size_;
}

template<typename T>
bool DEqueue<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
T& DEqueue<T>::front() const
{
    return head_ -> element_;
}

template<typename T>
T& DEqueue<T>::back() const
{
    return tail_ -> element_;
}

#endif