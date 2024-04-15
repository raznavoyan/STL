#ifndef __LIST__CPP__
#define __LIST__CPP__

#include "List.hpp"

template<typename T>
List<T>::List()
{
    head = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::List(T arg)
{
    List();
    push_back(arg);
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
size_t List<T>::size() const
{
    size_t count = 0;
    Node* tmp = this->head;
    while(tmp != nullptr){
        ++count;
        tmp = tmp->next;
    }
    return count;
}

template <typename T>
bool List<T>::empty() const
{
    if(this->head == nullptr){
        return true;
    }
    return false;
}

template<class T> 
void List<T>::clear(){
    while(!empty()){
        pop_back();
    }
}

template <typename T>
void List<T>::push_back(T element)
{
    if (head == nullptr){  
        tail = new Node(element, tail); 
        head = tail;
    }
    tail->next = new Node(element, tail);
    tail = tail->next;
}


template <typename T>
void List<T>::push_back()
{
    tail->next = new Node;
    this->tail = this->tail->next;
}

template <typename T>
void List<T>::pop_back()
{
    Node* tmp = head;
    while(tmp->next != tail){
        tmp = tmp->next;
    }
    delete tail;
    tail = tmp;
}

template <typename T>
T &List<T>::front()
{
// TODO: insert return statement here
    return head->data;
}

template <typename T>
T &List<T>::back()
{
// TODO: insert return statement here
    return tail->data;
}


#endif