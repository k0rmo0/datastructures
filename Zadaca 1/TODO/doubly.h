#ifndef _DOUBLY_
#define _DOUBLY_
#include<functional>
#include<iostream>
#include "ToDo.h"


template<typename T>
class Node
{
    public:
    T value_;
    Node<T>* prev_;
    Node<T>* next_;

    Node (T el = T{}, Node* n = {nullptr}, Node* p = {nullptr}) : value_{el}, prev_{n}, next_{p} {};
};

template<typename T>
class doublyList
{
    public:
    doublyList ();
    doublyList (size_t n);
    ~doublyList ();
    doublyList (const doublyList<T>& other);
    doublyList (doublyList<T>&& other);
    doublyList& operator=(const doublyList<T>& other);
    doublyList& operator=(doublyList<T>&& other);
  
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {  
        public: 
        Iterator(Node<T>* it) : it_{it} {}
        T& operator*() {return it_ -> value_;}
        Node<T>* get_it() const {return it_;}
        
        Iterator& operator++()
        {
            it_ = it_ -> next_;
            return *this;
        }

        Iterator operator++(int)
        {
            auto temp = *this;
            it_ = it_ -> next_;
            return temp;
        }

        Iterator& operator--()
        {
            it_ = it_ -> prev_;
            return *this;
        }

        Iterator operator--(int)
        {
            auto temp = *this;
            it_ = it_ -> prev_;
            return temp;
        }

        bool operator==(const Iterator& temp)
        {
            return it_ == temp.it_;
        }

        bool operator!=(const Iterator& temp)
        {
            return it_ != temp.it_;
        }

        private:
        Node<T>* it_;
    };

    
    Iterator begin() const{return Iterator(head_);}
    Iterator end() const{return Iterator(tail_ -> next_);}

    void print() const;
    bool isEmpty() const;
    void add(const T& item);
    Iterator find(std::function<bool (T)> fun);
    void remove(const Iterator& pos);
   


    private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

    void deleteList()
    {
        while (head_)
        {
            auto tmp = head_;
            head_ = head_ -> next_;
            delete tmp;
        }
        size_ = 0;
        head_ = tail_;
    }

    void copyList (const doublyList<T>& other)
    {
        head_ = new Node<T>(other.head_ -> value);
        tail_ = head_;
        auto temp = other.head_;
        size_ = other.size_;

        for(auto i = 1; i < other.size_; ++i)
        {
            tail_ = tail_ -> next_ = new Node<T>(T{}, tail_);
            temp = temp -> next_;

            tail_ -> value = temp -> value;
        }
    }
};

template<typename T>
doublyList<T>::doublyList() : head_{nullptr}, tail_{nullptr}, size_{0} {}

template<typename T>
doublyList<T>::doublyList(size_t n)
{
    head_ = new Node<T>();
    tail_ = head_;

    for (int i = 1; i < n; ++i)
    {
        tail_ = tail_ -> next_ = new Node<T>(T{}, tail_);
    }
}

template<typename T>
doublyList<T>::~doublyList()
{
    deleteList();
}

template<typename T>
doublyList<T>::doublyList(const doublyList<T>& other) : size_ {other.size_}
{
    if(size_ == 0)
    {
        head_= tail_ = nullptr;
    }
    else
    {
        copyList(other);
    }
}

template<typename T>
doublyList<T>::doublyList(doublyList<T>&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_}
{
    other.head_ = other.tail_ = nullptr;
}

template<typename T>
doublyList<T>& doublyList<T>:: operator=(const doublyList<T>& other)
{
    if(this == other)
       return *this;
    if(head_ !=nullptr)
    {    
        deleteList();
        copyList(other);
        return *this;
    }
}

template<typename T>
doublyList<T>& doublyList<T>:: operator=(doublyList<T>&& other) 
{
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
}


template<typename T>
bool doublyList<T>::isEmpty() const
{
    return (size_ == 0);
}

template<typename T>
void doublyList<T>::print () const
{
    int i = 1;
    auto temp = head_;
    if(isEmpty())
    {   
        std::cout << "Nemate obaveza ! " << std::endl <<std::endl;
        return;
    }
    else{
        std::cout << "ID | IME | OPIS | PRIORITET" << std::endl;
    while (temp != nullptr)
        {
            std::cout << temp -> value_ << " " <<std::endl;
            temp = temp -> next_;
            i++;
        }
    }
}

template<typename T>
typename doublyList<T>::Iterator doublyList<T>::find(std::function<bool (T)> fun)
{
    for (auto it = begin(); it != end(); ++it)
    {
        if(fun(*it))
            return it;
    }
    return end();
}

template<typename T>
void doublyList<T>::remove(const Iterator& pos)
{
    auto target = pos.get_it();
    if(size_ == 0)
        return;
    if(size_ == 1)
    {
        delete head_;
        head_ = tail_ = nullptr;
        size_ = 0;
        return;
    }
    if(target -> next_ == nullptr)
    {
        auto temp = target -> prev_;
        tail_ = temp;
        delete target;
        size_ --;
        return;
        
    }
    else if(target == head_)
    {
        head_ = head_ -> next_;
        head_ -> prev_ = nullptr;
        delete target;
        size_ --;
        return;
        
    }
    else
    {
        auto temp = target -> next_;
        auto temp2 = target -> prev_;
        temp2 -> next_ = temp;
        temp -> prev_ = temp2;
        delete target;
        size_ --;
    
       
    }
}

template<typename T>
void doublyList<T>::add (const T& item)
{
   
    bool swapped;

    auto newNode = new Node<T> (item);

    if(head_ == nullptr)
    {
        head_ = newNode;
        tail_ = head_;
        size_ ++;
    }
    else if(head_ -> value_ >= newNode -> value_)
    {
        newNode -> next_ = head_;
        newNode -> next_ -> prev_ = newNode;
        head_ = newNode;
        size_ ++;
    }
    else
    {
        swapped=false;
        auto pos = head_;
        auto lpos = nullptr;

        while(pos -> next_ != lpos && pos -> next_ -> value_ < newNode -> value_)
        {
            pos = pos -> next_;
        }
        
        newNode -> next_ = pos -> next_;
            if(pos -> next_ != nullptr)
                newNode -> next_ -> prev_ = newNode;
            pos -> next_ = newNode;
            newNode -> prev_ = pos;
        }
        size_ ++;
}

#endif