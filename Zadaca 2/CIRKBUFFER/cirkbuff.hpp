#ifndef _CIRKBUFF_
#define _CIRKBUFF_
#include<iostream>

template<typename T>
class cirkBuffer
{
    public:
    cirkBuffer(int size = 100);
    cirkBuffer(const cirkBuffer<T>& other);
    cirkBuffer(cirkBuffer<T>&& other);
    ~cirkBuffer();
    cirkBuffer<T>& operator=(const cirkBuffer<T>& other);
    cirkBuffer<T>& operator=(cirkBuffer<T>&& other);
    template<typename U>
    void enqueue(const U&& item);
    void dequeue();
    T front() const;
    size_t size() const;
    bool empty() const;

    private:
    int cap_;
    int size_;
    int frontel;
    int rear;
    T* list_;


    void reallocate()
    {
        auto temp3 = cap_;
        cap_ *=2;
        auto temp = new T[cap_];
        std::copy(list_ + frontel,list_ + temp3, temp);
        frontel = 0;
        std::copy(list_, list_ + rear, temp);
        rear = size_;
    }
};

template<typename T>
cirkBuffer<T>::cirkBuffer(int size)
{
   if (size < 0)
   {
       std::cout << "The array must be positive. Creating queue of size 100";
       cap_ = 100;
   }
   else
   {
       cap_ = size;
       size_ = 0;
       frontel = rear = -1;
       list_ = new T[cap_];
   }
}

template<typename T>
cirkBuffer<T>::cirkBuffer(const cirkBuffer<T>& other) : cap_{other.cap_}, size_{other.size_}
{
    if(size_ == 0)
    {
        frontel = rear = -1;
        return;
    }
    list_ = new T[cap_];
    std::copy(other.list_,other.list_ + cap_, list_);
    
}

template<typename T>
cirkBuffer<T>::cirkBuffer(cirkBuffer<T>&& other) : cap_{other.cap_}, size_{other.size_}, list_{other.list_}
{
    other.list_ = nullptr;
}

template<typename T>
cirkBuffer<T>::~cirkBuffer()
{
    delete [] list_;
}

template<typename T>
cirkBuffer<T>& cirkBuffer<T>::operator=(const cirkBuffer<T>& other)
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        if(size_ != 0)
        {
            cap_ = other.cap_;
            size_ = other.size_;
            frontel = other.frontel;
            rear = other.rear;
            delete [] list_;
            std::copy(other.list_, other.list_ + cap_, list_);
            //list_ = other.list_;
            return *this;
        }

    }
}

template<typename T>
cirkBuffer<T>& cirkBuffer<T>::operator=(cirkBuffer<T>&& other) 
{
    cap_ = other.cap_;
    size_ = other.size_;
    frontel = other.frontel;
    rear = other.rear;
    list_ = other.list_;
    other.list_ = nullptr;
    return *this;
}

template<typename T>
template<typename U>
void cirkBuffer<T>::enqueue(const U&& item)
{
    if((rear + 1)%size_ == front)
    {
        reallocate();
    }
    else
    {
        if(frontel == -1)
            frontel = 0;
        rear = (rear+1) % cap_;
        list_[rear] = (std::forward<U>(item));
        size_ ++;
    }
}

template<typename T>
void cirkBuffer<T>::dequeue()
{
    if(!empty())
    {
        if(frontel == rear)
        {
            frontel = rear = -1;
        }
        else
        {
            size_ --;
            frontel = (frontel + 1) % cap_;
        }
    }
    else
    {
        std::cout << "Cannot remove from empty queue !" << std::endl;
    }
}

template<typename T>
T cirkBuffer<T>::front() const 
{
    return list_[frontel];
}

template<typename T>
size_t cirkBuffer<T>::size() const
{
    return size_;
}

template<typename T>
bool cirkBuffer<T>::empty() const
{
    return size_ == 0;
}

#endif