using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class CEList<T>
{
    /// <summary>
    /// class to represent a list node
    /// </summary>
    private class CENode
    {
        public CENode prev;
        public CENode next;
        public T data;
        public CENode(T value)
        {
            data = value;
            prev = null;
            next = null;
        }
    }
    CENode first = null;
    CENode last = null;
    public CEList()
    {

    }
    /// <summary>
    /// Basic push operation
    /// </summary>
    /// <param name="data"></param>
    public void push(T data)
    {
        if (first == null)
        {
            first = last = new CENode(data);
        }
        else
        {
            CENode x = new CENode(data);
            x.prev = last;
            last.next = x;
            last = x;
        }
    }
    /// <summary>
    /// Basic pop operation
    /// </summary>
    /// <returns></returns>
    public T pop()
    {
        T data = last.data;
        if (first == last)
        {
            first = last = null;
        }
        else
        {
            last.prev.next = null;
            last = last.prev;
        }
        return data;
    }
    /// <summary>
    /// Clear the list
    /// </summary>
    public void clear()
    {
        first = last = null;
    }
    /// <summary>
    /// Get list size
    /// </summary>
    /// <returns>size of list</returns>
    public int size()
    {
        CENode x = first;
        int cnt = 0;
        while (x != null)
        {
            cnt++;
            x = x.next;
        }
        return cnt;
    }
    /// <summary>
    /// Get list represented as array
    /// </summary>
    /// <returns></returns>
    public T[] asArray()
    {
        int lenght = size();
        T[] array = new T[lenght];
        for (int i = 0; i < lenght; i++)
        {
            T x = pop();
            array[i] = x;
        }
        return array;
    }
}
