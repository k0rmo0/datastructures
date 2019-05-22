#ifndef _QUEUEARR_
#define _QUEUEARR_
#include<iostream>
#include<utility>

template<typename T>
class queue
{
    public:
    queue (int size);
    queue(const queue<T>& other);
    queue(queue<T>&& other);
    ~queue();
    queue<T>& operator=(const queue<T>& other);
    queue<T>& operator=(queue<T>&& other);
    template<typename U>
    void enqueue(U&& item);
    void dequeue();
    T front() const;
    size_t size() const;
    bool empty() const;

    private:

    size_t cap_;
    size_t size_;
    size_t frontel;
    size_t rear;
    T* que;

     void reallocate()
    {
        cap_ *= 2;
        auto temp = new T[cap_];
        std::copy(que + frontel, que + size_, temp);
        delete [] que;
        que = temp;
        frontel = 0;
        rear = size_ - 1;
        
    }
};

template<typename T>
queue<T>::queue(int size)
{
    if(size < 0)
    {
        cap_ = 100;
    }
    else
        cap_ = size;
    size_ = 0;
    frontel = rear = 0;
    que = new T[cap_];
}

template<typename T>
queue<T>::queue(const queue<T>& other) : cap_{other.cap_}, size_{other.size_}
{
    frontel = 0;
    rear = size_;
    que = new T[cap_];
    std::copy(other, other + size_, que);
}

template<typename T>
queue<T>::queue(queue<T>&& other) : cap_{other.cap_}, size_{other.size_}, que{other.que}
{
    other.que = nullptr;
}

template<typename T>
queue<T>::~queue()
{
    delete [] que;
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
    if(this == &other)
    {
        return *this;
    }
    else{
        if(size_ != 0)
        { 
            delete [] que;
            
        }

        cap_ = other.cap_;
        size_ = other.size_;
        frontel = 0;
        rear = other.rear;

        std::copy(other.que, other.que + size_, que);
        return *this;
    }
}

template<typename T>
queue<T>& queue<T>::operator=(queue<T>&& other)
{
    if(this != &other)
    {
    cap_ = other.cap_;
    size_ = other.size_;
    frontel = other.frontel;
    rear = other.rear;
    other.que = nullptr;
    return *this;
    }
}

template<typename T>
template<typename U>
void queue<T>::enqueue(U&& item)
{
    if(rear == cap_ - 1)
    {
        reallocate();
    }
    
    que[rear] = (std::forward<U>(item));
    size_ ++;
    rear ++;
}

template<typename T>
void queue<T>::dequeue()
{
    if(empty())
    {
        std::cout << "Queue is empty, cannot erase empty queue ! ";
        return;
    }
    if (frontel == rear)
        frontel = rear = 0;
    else
    {
        frontel ++;
        size_ --;
    }
}

template<typename T>
T queue<T>::front() const
{
    return que[frontel];
}

template<typename T>
size_t queue<T>::size() const
{
    return size_;
}

template<typename T>
bool queue<T>::empty() const
{
    return (size_ == 0);
}


#endif