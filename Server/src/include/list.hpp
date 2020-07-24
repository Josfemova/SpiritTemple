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
        explicit list(std::initializer_list<T> list);
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
        //extra
        static list<T> getInverse(list<T> &toInvert);
    };

    template <class T>
    list<T>::list(){};
    /**
     * @brief Construct a new list<T>::list object based on an initializer list
     * 
     * @tparam T type
     * @param list 
     */
    template <class T>
    list<T>::list(std::initializer_list<T> list)
    {
        for (T element : list)
        {
            push_back(element);
        }
    }
    /**
     * @brief Construct a new list<T>::list initialize a list based on a number matrix
     * 
     * @tparam T 
     * @param list 
     * @param size 
     */
    template <class T>
    list<T>::list(int *list, int size)
    {
        for (int i = 0; i < size; i++)
        {
            push_back(list[i]);
        }
    }
    /**
     * @brief Construct a new list<T>::list with a default value given up to size
     * 
     * @tparam T 
     * @param defaultVal 
     * @param size 
     */
    template <class T>
    list<T>::list(T defaultVal, int size)
    {
        for (int i = 0; i < size; i++)
        {
            push_back(defaultVal);
        }
    }
    /**
     * @brief gets element at index by reference
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
     * @brief gets element at index by reference
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
     * @brief returns first element data
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
     * @brief returns las element data
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
     * @brief returns is the list has elements or not
     * 
     * @tparam T 
     * @return true list has no elements
     * @return false list has at least one element
     */
    template <class T>
    bool list<T>::empty()
    {
        return (first == nullptr);
    }
    /**
     * @brief checks if given data is stored in one of the list nodes
     * 
     * @tparam T type
     * @param data data to look for
     * @return true list contains data
     * @return false list does not contain the data
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
     * @brief gets the size of the list (amount of elements stored)
     * 
     * @tparam T type
     * @return int size of list
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

    /**
     * @brief makes the list an empty list
     * 
     * @tparam T 
     * @return int error value
     */
    template <class T>
    int list<T>::clear()
    {
        first = nullptr;
        last = nullptr;
        return 0;
    }
    /**
     * @brief inserts the data at the given position, pushed data to the end if the index overflows
     * 
     * @tparam T type
     * @param data data that is to be inserted
     * @param index prefered insertion index
     * @return int error checking
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
     * @brief erases the element and the given index
     * 
     * @tparam T type
     * @param index index to erase
     * @return int 0 if not error found, -1 if an error was found
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
     * @brief pushes element to the end of the list
     * 
     * @tparam T type
     * @param data to be inserted
     * @return int error code
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
     * @brief pushes element to the beginning of the list
     * 
     * @tparam T type
     * @param data o be added
     * @return int error code
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
     * @brief erases last element and returns it's value
     * 
     * @tparam T type
     * @return T value stored in the erased node
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
     * @brief erases first element an returns it's value
     * 
     * @tparam T type
     * @return T value of erased node
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
     * @brief swaps the information betweeen to indexes
     * 
     * @tparam T type
     * @param indexA index to be swapped for index B
     * @param indexB index to be swapped with indexA
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
     * @brief gets list as an string value by sugin an stringstream
     * some data types might not be able to be printed this way
     * 
     * @tparam T type
     * @return std::string list as a string 
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
    /** 
     * @brief overload comparison operator to be able to check if two lists contain the same values
     * 
     * @tparam T type
     * @param x list at the left
     * @param y list at the right
     * @return true both contain the same values
     * @return false both contain different values
     */
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
    /**
     * @brief gets the reversed version of a given list
     * 
     * @tparam T type
     * @param toInvert list to reverse  
     * @return list<T> 
     */
    template<class T>
    list<T> list<T>::getInverse(list<T> &toInvert){
        list<T> inverted;
        for (auto x :toInvert)
        {
            inverted.push_front(x);
        }
        return inverted;
    }

}; // namespace ce

#endif //SPIRITTEMPLE_LIST_HPP
