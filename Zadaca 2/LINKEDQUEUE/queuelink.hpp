#ifndef _QUELINK_
#define _QUELINK_
#include<iostream>


template<typename T>
class Node
{
    public:
    T element_;
    Node<T>* next_;
    Node(T elem = T{}) : element_{elem}, next_{nullptr} {}
};

template<typename T>
class linkedQueue
{
    public:

    linkedQueue() : head_{nullptr}, tail{nullptr}, size_{0};
    linkedQueue(const linkedQueue<T>& other);
    ~linkedQueue();
    linkedQueue(linkedQueue<T>&& other);
    linkedQueue<T>& operator=(const linkedQueue<T>& other);
    linkedQueue<T>& operator=(linkedQueue<T>&& other);
    template<typename U>
    void enqueue(const U && item);
    void dequeue();
    T& front() const;
    size_t size() const;
    bool empty() const;

    private:

    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

    void deletequeue()
    {
        while(head_)
        {
            auto temp = head_;
            head_ = head_ -> next_;
            delete temp;
        }
        tail_ = head_;
    }

    void copyqueue(const linkedQueue<T>& other)
    {
        auto newqueue = new Node<T>(other.head_ -> element_);
        auto temp = other.head_ -> next_;
        size_ = other.size_;
        tail_ = head_;

        for (int i = 1; i < size_; ++i)
        {
            tail_ = tail_ -> next_ = new Node<T>(temp -> element_);
            temp -> next_;
        }
    }
};



template<typename T>
linkedQueue<T>::linkedQueue(const linkedQueue<T>& other)
{
    if(other.size_ == 0)
    {
        head_ = tail_ = nullptr;
    }
    copyqueue(other);
}

template<typename T>
linkedQueue<T>::~linkedQueue()
{
    deletequeue();
}

template<typename T>
linkedQueue<T>::linkedQueue(linkedQueue<T>&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_}
{
    other.head_ = other.tail_ = nullptr;
}

template<typename T>
linkedQueue<T>& linkedQueue<T>::operator=(const linkedQueue<T>& other)
{
    if(this == &other)
        return *this;
    if (other.size_ != 0)
    {
        deletequeue();
        copyqueue(other);
        return *this;
    }
    else
    {
        return *this
    }
    
}

template<typename T>
linkedQueue<T>& linkedQueue<T>::operator=(linkedQueue<T>&& other)
{
    size_ = ohter.size_;
    deletequeue();
    head_ = other.head_;
    tail_ = other.tail_;

    other.head_ = other.tail_ = nullptr;

    return *this;
}

template<typename T>
template<typename U>
void linkedQueue<T>::enqueue(const U&& item)
{
    auto temp = new Node<T>(std::forward<U>(item));
    tail_ -> next_ = temp;
    tail_ = temp;
}

template<typename T>
void linkedQueue<T>::dequeue()
{
    auto temp = head_;
    head_ = head_ -> next_;
    delete temp;
}

template<typename T>
T& linkedQueue<T>::front() const
{
    return head_ -> value_;
}

template<typename T>
size_t linkedQueue<T>::size() const
{
    return size_;
}

template<typename T>
bool linkedQueue<T>::empty() const
{
    return size_ == 0;
}

#endif