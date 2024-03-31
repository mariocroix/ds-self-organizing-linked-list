#ifndef SOLL_TPP
#define SOLL_TPP

#include "soll.hpp"

template <typename T>
typename SOList<T>::size_type SOList<T>::_size = 0;

template <typename T>
SOList<T>::SOList()
    : _head {nullptr}
    , _tail {nullptr}
    , _ascHead {nullptr}
    , _descHead {nullptr} {}

template <typename T>
SOList<T>::~SOList()
{
    Node* curr = _head;
    while (_size != 0)
    {
        --_size;
        Node* tmp = curr;
        curr = curr->_next;
        delete tmp;
    }
}

template <typename T>
bool SOList<T>::empty() const
{
    return static_cast<bool>(_size);
}

template <typename T>
void SOList<T>::push_back(SOList::const_reference data)
{
    Node* newNode = new Node(data);

    if (_size == 0)
    {
        _head = newNode;
        _tail = newNode;
        _ascHead = newNode;
        _descHead = newNode;
    }
    else
    {
        _tail->_next = newNode;
        newNode->_prev = _tail;
        _tail = newNode;

        insert_in_sorted_list(newNode);
    }

    ++_size;
}

template <typename T>
void SOList<T>::pop_back()
{
    if (_size == 0)
    {
        throw std::out_of_range("The list is empty.");
    }

    if (_size == 1)
    {
        delete _tail;
        _head = nullptr;
        _tail = nullptr;
        _ascHead = nullptr;
        _descHead = nullptr;
    }
    else
    {
        remove_from_sorted_list(_tail);
        _tail = _tail->_prev;
        _tail->_next = nullptr;
    }

    --_size;
}

template <typename T>
void SOList<T>::push_front(SOList::const_reference data)
{
    Node* newNode = new Node(data);

    if (_size == 0)
    {
        _head = newNode;
        _tail = newNode;
        _ascHead = newNode;
        _descHead = newNode;
    }
    else
    {
        _head->_prev = newNode;
        newNode->_next = _head;
        _head = newNode;

        insert_in_sorted_list(newNode);
    }

    ++_size;
}

template <typename T>
void SOList<T>::pop_front()
{
    if (_size == 0)
    {
        throw std::out_of_range("The list is empty");
    }

    if (_size == 1)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _ascHead = nullptr;
        _descHead = nullptr;
    }
    else
    {

        remove_from_sorted_list(_head);
        _head = _head->_next;
        delete _head->_prev;
        _head->_prev = nullptr;
    }

    --_size;
}

template <typename T>
void SOList<T>::insert(size_type pos, SOList::const_reference data)
{
    if (pos < 0 || pos >= _size)
    {
        throw std::out_of_range("Invalid position.");
    }

    if (pos == 0)
    {
        push_front(data);
    }
    else if (pos == _size)
    {
        push_back(data);
    }
    else
    {
        Node* newNode = new Node(data);
        Node* curr = _head;

        for (size_t i = 0; i < pos - 1; ++i)
        {
           curr = curr->_next;
        }

        newNode->_next = curr->_next;
        curr->_next->_prev = newNode;
        curr->_next = newNode;
        newNode->_prev = curr;

        insert_in_sorted_list(newNode);

        ++_size;
    }
}

template <typename T>
void SOList<T>::remove(SOList::size_type pos)
{
    if (pos < 0 || pos >= _size)
    {
        throw std::out_of_range("Invalid position.");
    }

    if (pos == 0)
    {
        pop_front();
    }
    else if (pos == _size - 1)
    {
        pop_back();
    }
    else
    {
        Node* curr = _head;
        for (size_t i = 0; i < pos - 1; ++i)
        {
            curr = curr->_next;
        }
        curr->_next = curr->_next->_next;
        Node* tmp = curr->_next->_prev;
        curr->_next->_prev = curr;

        remove_from_sorted_list(tmp);

        --_size;
    }
}

template <typename T>
void SOList<T>::print() const
{
    Node* curr = _head;
    while (curr != nullptr)
    {
        std::cout << curr->_data << " ";
        curr = curr->_next;
    }
    std::cout << std::endl;
}

template <typename T>
void SOList<T>::print_sorted() const
{
    Node* curr = _descHead;
    while (curr != nullptr)
    {
        std::cout << curr->_data << " ";
        curr = curr->_asc;
    }
    std::cout << std::endl;
}

template <typename T>
void SOList<T>::insert_in_sorted_list(SOList::Node* node)
{
    Node* curr = _descHead;
    size_t pos = -1;

    while (curr != nullptr)
    {
        ++pos;
        if (curr->_data > node->_data)
        {
            if (pos == 0)
            {
                push_front_in_sorted_list(node);
                break;
            }
            else
            {
                curr->_desc->_asc = node;
                node->_desc = curr->_desc;
                curr->_desc = node;
                node->_asc = curr;
                break;
            }
        }
        else if (pos == _size - 1)
        {
            push_back_in_sorted_list(node);
        }

        curr = curr->_asc;
    }
    print_sorted();
}

template <typename T>
void SOList<T>::remove_from_sorted_list(SOList::Node* node)
{
    size_t pos = -1;
    Node* curr = _descHead;

    while (curr != nullptr)
    {
        ++pos;
        if (curr == node)
        {
            if (pos == 0)
            {
                pop_front_from_sorted_list();
                break;
            }

            if (pos == _size - 1)
            {
                pop_back_from_sorted_list();
                break;
            }

            curr->_desc->_asc = curr->_asc;
            curr->_asc->_desc = curr->_desc;
        }

        curr = curr->_asc;
    }
}

template <typename T>
void SOList<T>::push_back_in_sorted_list(SOList::Node* node)
{
    _ascHead->_asc = node;
    node->_desc = _ascHead;
    _ascHead = node;
}

template <typename T>
void SOList<T>::push_front_in_sorted_list(SOList::Node* node)
{
    _descHead->_desc = node;
    node->_asc = _descHead;
    _descHead = node;
}

template <typename T>
void SOList<T>::pop_back_from_sorted_list()
{
    _ascHead = _ascHead->_desc;
    _ascHead->_asc = nullptr;
}

template <typename T>
void SOList<T>::pop_front_from_sorted_list()
{
    _descHead = _descHead->_asc;
    _descHead->_desc = nullptr;
}

template <typename T>
SOList<T>::Node::Node()
        : _prev {nullptr}
        , _next {nullptr}
        , _desc {nullptr}
        , _asc {nullptr}
        , _data {value_type()} {}

template <typename T>
SOList<T>::Node::Node(SOList::const_reference _data)
        : _prev {nullptr}
        , _next {nullptr}
        , _desc {nullptr}
        , _asc {nullptr}
        , _data {_data} {}

template <typename T>
void merge(SOList<T>& right, SOList<T>& left)
{

}

#endif // SOLL_TPP