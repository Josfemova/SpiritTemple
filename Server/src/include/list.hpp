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
    /**
     * @brief Node class used to store data in a doubly linked list
     * 
     * @tparam T 
     */
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
        /**
         * @brief 
         * 
         * @return std::string 
         */
        std::string toString()
        {
            std::stringstream ss;
            ss << data;
            return ss.str();
        }

        template <class E>
        /**
         * @brief 
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        friend bool operator==(const list<E> &x, const list<E> &y);
    };
    /**
     * @brief allows for each iteration trough list elements
     * 
     * @tparam T data type of list to be iterated over
     */
    template <class T>
    struct listIterator
    {
        std::shared_ptr<Node<T>> n;
        listIterator<T>(std::shared_ptr<Node<T>> node) : n(node) {} //constructor
        bool operator!=(listIterator<T> rhs) { return n != rhs.n; }
        //Node<T> &operator*() { return *n; }
        T &operator*()
        {
            return n->data;
        }
        void operator++() { n = n->next; }
        void operator--() { n = n->prev; }
    };
    template <class T>
    /**
     * @brief 
     * 
     */
    class list
    {
    private:
        std::shared_ptr<Node<T>> first = nullptr;
        std::shared_ptr<Node<T>> last = nullptr;

    public:
        list();
        explicit list(std::initializer_list<int> list);
        explicit list(int *list, int size);
        explicit list(T defaultValue, int size);
        //access
        /**
         * @brief gives an iterator pointing to the first element
         * 
         * @return listIterator<T> 
         */
        listIterator<T> begin()
        {
            return first;
        };
        /**
         * @brief gives an iterator pointing to the final element of the list
         * 
         * @return listIterator<T> 
         */
        listIterator<T> end()
        {
            return last->next;
        };
        T &at(int position);
        T &operator[](int position);
        T &front();
        T &back();
        //information
        bool empty();
        bool contains(T data) const;
        int size() const;
        //modifiers
        int clear();
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
    /**
     * @brief Construct a new list<T>::list object
     * 
     * @tparam T 
     * @param list 
     */
    template <class T>
    list<T>::list(std::initializer_list<int> list)
    {
        for (T element : list)
        {
            push_back(element);
        }
    }
    template <class T>
    list<T>::list(int *list, int size)
    {
        for (int i = 0; i < size; i++)
        {
            push_back(list[i]);
        }
    }
    template <class T>
    list<T>::list(T defaultVal, int size)
    {
        for (int i = 0; i < size; i++)
        {
            push_back(defaultVal);
        }
    }
    /**
     * @brief 
     * 
     * @tparam T 
     * @param index 
     * @return T& 
     */
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @param index 
     * @return T& 
     */
    template <class T>
    T &list<T>::operator[](int index)
    {
        return at(index);
    }
    /**
     * @brief 
     * 
     * @tparam T 
     * @return T& 
     */
    template <class T>
    T &list<T>::front()
    {
        return first->data;
    }
    /**
     * @brief 
     * 
     * @tparam T 
     * @return T& 
     */
    template <class T>
    T &list<T>::back()
    {
        return last->data;
    }
    /**
     * @brief 
     * 
     * @tparam T 
     * @return true 
     * @return false 
     */
    template <class T>
    bool list<T>::empty()
    {
        return (first == nullptr);
    }
    /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @return true 
     * @return false 
     */
    template <class T>
    bool list<T>::contains(T data) const
    {
        std::shared_ptr<Node<T>> it = first;
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @return int 
     */
    template <class T>
    int list<T>::size() const
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
    int list<T>::clear()
    {
        first = nullptr;
        last = nullptr;
        return 0;
    }
    /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @param index 
     * @return int 
     */
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
            std::shared_ptr<Node<T>> x(new Node<T>(data));
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @param index 
     * @return int 
     */
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @return int 
     */
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @param data 
     * @return int 
     */
    template <class T>
    int list<T>::push_front(T data)
    {
        std::shared_ptr<Node<T>> x(new Node<T>(data));

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
    /**
     * @brief 
     * 
     * @tparam T 
     * @return T 
     */
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @return T 
     */
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @param indexA 
     * @param indexB 
     * @return int 
     */
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
    /**
     * @brief 
     * 
     * @tparam T 
     * @return std::string 
     */
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
