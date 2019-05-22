#ifndef _BST_
#define _BST_
#include<iostream>

template<typename k, typename val>
class Node
{
    public:
    k key_;
    val value_;
    Node<k,val>* left_;
    Node<k,val>* right_;

    Node(const k& key, const val& value) : key_{key}, value_{value}, left_{nullptr}, right_{nullptr} {}
};


template<typename k, typename val>
class BST 
{
    public:
    BST() : root_{nullptr} {}
    BST (const BST& other);
    BST (BST&& other);
    BST& operator=(const BST& other);
    BST& operator=(BST&& other);
    ~BST();
    BST& insert (const k& item, const val& item1);
    void remove(const k& target);
    val& find(const k& item);
    void print_preorder() const;
    void print_postorder() const;
    void print_inorder() const;

    private:
    Node<k,val>* root_;

    void copy(Node<k,val>* &into,Node<k,val>* source)
    {
        if(source == nullptr)
            into = nullptr;
        else
        {
            into = new Node<k,val>(source -> key_, source -> value_);
            copy(into -> left_, source -> left_);
            copy(into -> right_, source -> right_);
        }
    }

    void destroy(Node<k,val>* &tree)
    {
        destroy(tree -> left_);
        destroy(tree -> right_);
        delete tree;
        tree = nullptr;
    }

    void deleteItem(Node<k,val>* & target)
    {
        Node<k,val>* temp;
        Node<k,val>* previous;
        Node<k,val>* temp2;

        if(target -> left_ == nullptr && target -> right_ == nullptr)
        {
            temp2 = target;
            target = nullptr;
            delete temp2;
        }
        else if(target -> left_ == nullptr)
        {
            temp2 = target;
            target = temp2 -> right_;
            delete temp2;
        }
        else if (target -> right_ == nullptr)
        {
            temp2 = target;
            target = target -> left_;
            delete temp2;
        }
        else
        {
            temp = target -> left_;
            previous = nullptr;
            while (temp -> right_ != nullptr)
            {
                previous = temp;
                temp = temp -> right_;
            }

            target -> key_ = temp -> key_;

            if(previous == nullptr)
                target -> left_ = temp -> left_;
            else
            {
                previous -> right_ = temp -> right_;
            }

            delete temp;
        }
    }

void inorder (Node<k,val>* item) const
{
    if(item != nullptr)
    {
        inorder(item -> left_);
        std::cout << "KEY: " << item -> key_ << "VALUE: " << item -> value_ << std::endl;
        inorder(item -> right_);
    }
}

void postorder (Node<k,val>* item) const
{
    if(item != nullptr)
    {
        postorder(item -> left_);
        postorder(item -> right_);
        std::cout << "KEY: " << item -> key_ << " " << "VALUE: " << item -> value_ << std::endl;
    }
}

void preorder (Node<k,val>* item) const
{
    if(item != nullptr)
    {
        std::cout << "KEY: " << item -> key_ << " " << "VALUE: " << item -> value_ << std::endl;
        preorder(item -> left_);
        preorder(item -> right_);
    }
}
};

template<typename k, typename val>
BST<k,val>::BST(const BST<k,val>& other)
{
    if (other.root_ == nullptr)
        root_ = nullptr;
    else
        copy(root_, other.root_);
}

template<typename k, typename val>
BST<k,val>::BST(BST<k,val>&& other) : root_{other.root_}
{
    other.root_ = nullptr;
}

template<typename k, typename val>
BST<k,val>& BST<k,val>::operator=(const BST<k,val>& other)
{
    if(this == &other)
        return *this;
    else
    {
        if(root_ != nullptr)
            destroy(root_);
        copy(root_, other.root_);
        return *this;
    }
}

template<typename k, typename val>
BST<k,val>& BST<k,val>::operator=(BST<k,val>&& other) 
{
    root_ = other.root_;
    other.root_ = nullptr;   
}

template<typename k, typename val>
BST<k,val>::~BST()
{
    destroy(root_);
}

template<typename k, typename val>
BST<k,val>& BST<k,val>::insert(const k& item, const val& item1)
{
    auto element = new Node<k,val>(item, item1);
    Node<k,val>* previous;
    if (root_ == nullptr)
       { 
           root_ = element;
           return *this;
       }
    else
    {
        auto temp = root_;
        previous = temp;
        while(temp != nullptr)
        {
            previous = temp;
            if(temp -> key_ == element -> key_)
            {
                std::cout << "Cannot insert element with same key !" << std::endl;
                return *this;
            }
            else if (temp -> key_ > element -> key_)
                temp = temp -> left_;
            else if (temp -> key_ < element -> key_)
                temp = temp -> right_;
        }
        if(previous -> key_ > element -> key_)
            previous -> left_ = element;
        else
        previous -> right_ = element;
        return *this;
    }
}

template<typename k, typename val>
val& BST<k,val>::find(const k& item)
{
    auto temp = root_;

    if (root_ == nullptr)
    {
        std::cout << "Tree is empty !";
    }
    else
    {
         while (temp != nullptr)
         {
            if(temp -> key_ == item)
                return temp -> value_;
            else if (temp -> key_ < item)
                temp = temp -> right_;
            else if (temp -> key_ > item)
                temp = temp -> left_;
         }
         std::cout << "Item not found !" << std::endl;
    }
}

template<typename k, typename val>
void BST<k,val>::remove(const k& target)
{
    auto temp = root_;
    Node<k,val>* previous;
    bool found = false;

    if(root_ == nullptr)
        std::cout << "Cannot delete from empty tree !" ;
    else
    {
        previous = temp;
        while (temp != nullptr && !found)
        {
            if(temp -> key_ == target)
                found = true;
            else
            {
                previous = temp;
                if(temp -> key_ > target)
                    temp = temp -> left_;
                else
                    temp = temp -> right_;
            }
        
        }

        if(temp == nullptr)
            std::cout << "Item that you want to delete is not in the tree !" << std::endl;
        else if(found)
        {
            if(temp == root_)
                deleteItem(root_);
            else if (previous -> key > target)
                deleteItem(previous -> left_);
            else
            {
                deleteItem(previous -> right_);
            }
        }
    }
}

template<typename k,typename val>
void BST<k,val>::print_inorder() const
{
    inorder(root_);
}

template<typename k, typename val>
void BST<k,val>::print_postorder() const
{
    postorder(root_);
}

template<typename k,typename val>
void BST<k,val>::print_preorder() const
{
    preorder(root_);
}

#endif