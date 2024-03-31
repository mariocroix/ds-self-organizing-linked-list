#ifndef SOLL_HPP
#define SOLL_HPP

#include <iostream>

template <typename T>
class SOList
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    SOList();
    ~SOList();
    bool empty() const;
    void push_back(const_reference);
    void pop_back();
    void push_front(const_reference);
    void pop_front();
    void insert(size_type, const_reference);
    void remove(size_type);
    void print() const;
    void print_sorted() const;

private:
    struct Node
    {
        Node* _prev;
        Node* _next;
        Node* _desc;
        Node* _asc;
        value_type _data;

        Node();
        explicit Node(const_reference);
    };

    Node* _head;
    Node* _tail;
    Node* _ascHead;
    Node* _descHead;
    static size_type _size;

    void insert_in_sorted_list(Node*);
    void remove_from_sorted_list(Node*);
    void push_back_in_sorted_list(Node*);
    void push_front_in_sorted_list(Node*);
    void pop_back_from_sorted_list();
    void pop_front_from_sorted_list();
};

// to do
template <typename T>
void merge(SOList<T>&, SOList<T>&);

#include "soll.tpp"

#endif // SOLL_HPP