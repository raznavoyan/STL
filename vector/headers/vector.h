#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <iostream>
#include <memory>
#include <initializer_list>

namespace g3
{

template <typename T, typename Allocator = std::allocator<T>>
class vector
{
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;    
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using difference_type = int;

public:
    class const_iterator;
    class iterator;
    class const_reverse_iterator;
    class reverse_iterator;

public:

    vector();
    vector(const vector& rhv);
    vector(vector&& rhv);
    vector(std::initializer_list<value_type> init);
    vector(size_type size, const_reference val = value_type{});
    template <typename InputIt>
    vector(InputIt first, InputIt last);
    ~vector();

public:

    const vector& operator=(const vector& rhv);
    const vector& operator=(vector&& rhv) noexcept;

    allocator_type get_allocator();

public:
    reference at(size_type pos);
    const_reference at(size_type pos) const;

    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

public:
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    
    iterator rbegin();
    const_iterator rbegin() const;
    const_iterator crbegin() const;
    
    iterator rend();
    const_iterator rend() const;
    const_iterator crend() const;
    
public:
    bool empty() const;
    size_type size() const;
    size_type capacity() const;

    void reserve(size_type new_cap);

public:
    void clear() noexcept;

    iterator insert(const_iterator pos, const_reference val);
    iterator insert(const_iterator pos, size_type count, const_reference val);
    iterator insert(const_iterator pos, std::initializer_list<value_type> init);
    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const_reference val);
    void pop_back();

    void resize(size_type new_size, const_reference val = value_type{});

public:
    bool operator==(const vector& other) const;
    bool operator!=(const vector& other) const;
    bool operator<(const vector& other) const;
    bool operator<=(const vector& other) const;
    bool operator>(const vector& other) const;
    bool operator>=(const vector& other) const;

private:
    int compare(const vector& other) const;
    
private:
    size_type size_;
    size_type capacity_;
    pointer arr_;
    allocator_type allocator_;
};

template <typename T, typename Allocator>
class vector<T, Allocator>::const_iterator
{
    friend class vector<T, Allocator>;
protected:
    pointer ptr;
public:
    const_iterator(pointer ptr);
    const_iterator() = default;
    const_iterator(const const_iterator&) = default;      
    const_iterator(const_iterator&&) = default;

    const_iterator& operator=(const const_iterator&) = default;      
    const_iterator& operator=(const_iterator&&) = default;

    const_iterator operator+(size_type n) const;      
    const_iterator operator-(size_type n) const;

    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    const_reference operator[](size_type pos) const;

    bool operator==(const const_iterator& other) const;      
    bool operator!=(const const_iterator& other) const;      
    bool operator<(const const_iterator& other) const;      
    bool operator<=(const const_iterator& other) const;      
    bool operator>(const const_iterator& other) const;      
    bool operator>=(const const_iterator& other) const;      
};

template <typename T, typename Allocator>
class vector<T, Allocator>::iterator : vector<T, Allocator>::const_iterator
{
    friend class vector<T, Allocator>;
private:
    iterator(pointer ptr);
public:
    iterator() = default;
    iterator(const iterator&) = default;      
    iterator(iterator&&) = default;

    iterator& operator=(const iterator&) = default;      
    iterator& operator=(iterator&&) = default;

    iterator operator+(size_type n) const;      
    iterator operator-(size_type n) const;

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    reference operator*();
    pointer operator->();

    reference operator[](size_type pos) const;
};


template <typename T, typename Allocator>
class vector<T, Allocator>::const_reverse_iterator
{
    friend class vector<T, Allocator>;
protected:
    pointer ptr;
private:
    const_reverse_iterator(pointer ptr);
public:
    const_reverse_iterator() = default;
    const_reverse_iterator(const const_reverse_iterator&) = default;      
    const_reverse_iterator(const_reverse_iterator&&) = default;

    const_reverse_iterator& operator=(const const_reverse_iterator&) = default;      
    const_reverse_iterator& operator=(const_reverse_iterator&&) = default;

    const_reverse_iterator operator+(size_type n) const;      
    const_reverse_iterator operator-(size_type n) const;

    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);
    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    const_reference operator[](size_type pos) const;

    bool operator==(const const_reverse_iterator& other) const;      
    bool operator!=(const const_reverse_iterator& other) const;      
    bool operator<(const const_reverse_iterator& other) const;      
    bool operator<=(const const_reverse_iterator& other) const;      
    bool operator>(const const_reverse_iterator& other) const;      
    bool operator>=(const const_reverse_iterator& other) const;      
};

template <typename T, typename Allocator>
class vector<T, Allocator>::reverse_iterator : vector<T, Allocator>::const_reverse_iterator
{
    friend class vector<T, Allocator>;
private:
    reverse_iterator(pointer ptr);
public:
    reverse_iterator() = default;
    reverse_iterator(const reverse_iterator&) = default;      
    reverse_iterator(reverse_iterator&&) = default;

    reverse_iterator& operator=(const reverse_iterator&) = default;      
    reverse_iterator& operator=(reverse_iterator&&) = default;

    reverse_iterator operator+(size_type n) const;      
    reverse_iterator operator-(size_type n) const;

    reverse_iterator& operator++();
    reverse_iterator operator++(int);
    reverse_iterator& operator--();
    reverse_iterator operator--(int);

    reference operator*();
    pointer operator->();

    reference operator[](size_type pos) const;
};

#include "vector.cpp"

}
#endif
