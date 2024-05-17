#ifndef __QUEUE__H__
#define __QUEUE__H__

#include <deque>

namespace g3
{

template <typename T, typename Container = std::deque<T>>
class queue
{
public:
    using container_type = Container;
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
    queue();
    queue(const queue& rhv);
    queue(queue&& rhv);
    queue(std::initializer_list<value_type> init);
    template <typename InputIt>
    queue(InputIt first, InputIt last);
    ~queue();

    const queue& operator=(const queue& rhv);
    const queue& operator=(queue&& rhv);

public:
    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    bool empty() const;
    size_type size() const;

    void push(const_reference val);
    void pop();

public:

    bool operator==(const queue& other);
    bool operator!=(const queue& other);
    bool operator<(const queue& other);
    bool operator<=(const queue& other);
    bool operator>(const queue& other);
    bool operator>=(const queue& other);


private:
    Container ob;
};


}

#include "queue.cpp"

#endif