#ifndef SPIRITTEMPLE_LIST_HPP
#define SPIRITTEMPLE_LIST_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include <memory>

namespace ce
{
    template <class T>
    class list;
    template <class T>
    class Node
    {
    private:
        friend class list<T>;
        explicit Node(T newdata) : data(newdata) {}

    public:
        std::shared_ptr<Node<T>> prev = nullptr;
        std::shared_ptr<Node<T>> next = nullptr;
        T data;
        std::string toString()
        {
            std::stringstream ss;
            ss << data;
            return ss.str();
        }
        template <class E>
        friend bool operator==(const list<E> &x, const list<E> &y);
    };

    template <class T>
    class list
    {
    private:
        std::shared_ptr<Node<T>> first = nullptr;
        std::shared_ptr<Node<T>> last = nullptr;

    public:
        list();
        explicit list(std::initializer_list<int> list);
        //access
        T &at(int position);
        T &operator[](int position);
        T &front();
        T &back();
        //information
        bool empty();
        bool contains(T data);
        int size();
        //modifiers
        int insert(T data, int index);
        int erase(int index);
        int push_back(T data);
        int push_front(T data);
        T pop_back();
        T pop_front();
        int swap(int indexA, int indexB);
        std::string toString();
        template <class E>
        friend bool operator==(list<E> &x, list<E> &y);
    };

    template <class T>
    list<T>::list(){};
    template <class T>
    list<T>::list(std::initializer_list<int> list)
    {
        for (T element : list)
        {
            push_back(element);
        }
    }
    //access
    template <class T>
    T &list<T>::at(int index)
    {
        int i = 0;
        std::shared_ptr<Node<T>> it = first;
        while (i != index)
        {
            ++i;
            it = it->next;
            if (it == nullptr)
            {
                throw 10; // invalid index exception
            }
        }
        return it->data;
    }
    template <class T>
    T &list<T>::operator[](int index)
    {
        return at(index);
    }
    template <class T>
    T &list<T>::front()
    {
        return first->data;
    }
    template <class T>
    T &list<T>::back()
    {
        return last->data;
    }
    template <class T>
    bool list<T>::empty()
    {
        return (first == nullptr);
    }
    template <class T>
    bool list<T>::contains(T data)
    {
        Node<T> *it = first;
        while (it != nullptr)
        {
            if (it->data == data)
            {
                return true;
            }
            it = it->next;
        }
        return false;
    }
    template <class T>
    int list<T>::size()
    {
        int x = 0;
        std::shared_ptr<Node<T>> it = first;
        while (it != nullptr)
        {
            ++x;
            it = it->next;
        }
        return x;
    }

    //modifiers
    template <class T>
    int list<T>::insert(T data, int index)
    {
        if (index >= (size() - 1))
        { //end or bigger than end
            push_back(data);
        }
        else if (index == 0)
        { //first element
            push_front(data);
        }
        else
        { //index in bounds
            std::shared_ptr<Node<T>> x = new Node<T>(data);
            std::shared_ptr<Node<T>> front = first;

            int i = 0;
            while (i != index)
            {
                front = front->next;
            }

            std::shared_ptr<Node<T>> rear = front->prev;
            x->prev = rear;
            x->next = front;
            rear->next = x;
            front->prev = x;
        }
        return 0;
    }
    template <class T>
    int list<T>::erase(int index)
    {
        if (index > (size() - 1))
        {
            return -1;
        }
        else if (index == 0)
        {
            pop_front();
        }
        else if (index == (size() - 1))
        {
            pop_back();
        }
        else
        {
            std::shared_ptr<Node<T>> toDel = first;
            for (int i = 0; i < index; i++)
            {
                toDel = toDel->next;
            }
            toDel->prev->next = toDel->next;
            toDel->next->prev = toDel->prev;
        }
        return 0;
    }
    template <class T>
    int list<T>::push_back(T data)
    {
        std::shared_ptr<Node<T>> x(new Node<T>(data));

        if (empty())
        { //empty
            first = last = x;
        }
        else
        { //not empty
            last->next = x;
            x->prev = last;
            last = x;
        }
        return 0;
    }
    template <class T>
    int list<T>::push_front(T data)
    {
        std::shared_ptr<Node<T>> x = new Node<T>(data);

        if (empty())
        { //empty
            first = last = x;
        }
        else
        { //not empty
            first->prev = x;
            x->next = first;
            first = x;
        }
        return 0;
    }
    template <class T>
    T list<T>::pop_back()
    {

        T value = last->data;
        if (last->prev == nullptr)
        {
            first = last = nullptr;
        }
        else
        {
            std::shared_ptr<Node<T>> temp = last;
            last = temp->prev;
            last->next = nullptr;
        }
        return value;
    }
    template <class T>
    T list<T>::pop_front()
    {
        T value = first->data;
        if (first->next == nullptr)
        {
            first = last = nullptr;
        }
        else
        {
            std::shared_ptr<Node<T>> temp = first;
            first = temp->next;
            first->prev = nullptr;
        }
        return value;
    }
    template <class T>
    int list<T>::swap(int indexA, int indexB)
    {
        T &a = at(indexA);
        T &b = at(indexB);
        T temp = a;
        a = b;
        b = temp;
        return 0;
    }
    template <class T>
    std::string list<T>::toString()
    {

        int n = size() - 1;
        std::shared_ptr<Node<T>> it = first;
        std::string stringForm = "[";
        for (int i = 0; i <= n; i++)
        {
            stringForm += (it->toString());
            if (it->next != nullptr)
            {
                stringForm += ',';
            }
            it = it->next;
        }
        stringForm += ']';
        return stringForm;
    }
    template <class T>
    bool operator==(list<T> &x, list<T> &y)
    {
        std::shared_ptr<Node<T>> itx = x.first;
        std::shared_ptr<Node<T>> ity = y.first;
        if (x.size() != y.size())
        {
            return false;
        }
        while (itx != nullptr)
        {
            if (itx->data != ity->data)
            {
                return false;
            }
            itx = itx->next;
            ity = ity->next;
        }
        return true;
    }

}; // namespace ce

#endif //SPIRITTEMPLE_LIST_HPP
