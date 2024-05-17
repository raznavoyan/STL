#ifndef __STACK__H__
#define __STACK__H__

#include <deque>

namespace g3
{

template <typename T, typename Container = std::deque<T>>
class stack
{
public:
    using container_type = Container;
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
    stack();
    stack(const stack& rhv);
    stack(stack&& rhv);
    stack(std::initializer_list<value_type> init);
    template <typename InputIt>
    stack(InputIt first, InputIt last);
    ~stack();

    const stack& operator=(const stack& rhv);
    const stack& operator=(stack&& rhv);

public:
    reference top();
    const_reference top() const;

    bool empty() const;
    size_type size() const;

    void push(stack&& rhv);
    void push(const_reference val);
    void pop();

public:
        bool operator==(const stack& other) const {
            return ob == other.ob;
        }

        bool operator!=(const stack& other) const {
            return ob != other.ob;
        }

        bool operator<(const stack& other) const {
            return ob < other.ob;
        }

        bool operator<=(const stack& other) const {
            return ob <= other.ob;
        }

        bool operator>(const stack& other) const {
            return ob > other.ob;
        }

        bool operator>=(const stack& other) const {
            return ob >= other.ob;
        }

private:
    Container ob;
};


}

#include "stack.cpp"

#endif