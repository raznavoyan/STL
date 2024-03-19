#ifndef __LINKED__LIST__
#define __LINKED__LIST__
#include<iostream>

template<typename T>
class List{
public:
    typedef std::size_t size_t;


private:
    /// @brief Node info
    struct Node
    {
        T data;
        Node* next;
        Node():
        data(0),
        next(nullptr)
        {};
    };

public:
    List();
    List(T arg); 
    ~List();

    size_t size() const; //O(n)
    bool empty() const; //O(1)
    ///void resize(const size_t size); //O(n) //O(1)
    void clear(); //O(n)

    // void push_front(T element); //O(1)
    // void pop_front(); //O(1)
    void push_back(T element); //O(1)
    void push_back();
    void pop_back(); //O(n)


    T& front(); //O(1)
    T& back(); //O(1)

private:
    Node* head;
    Node* tail;
};


#include "../sources/List.cpp"
#endif
