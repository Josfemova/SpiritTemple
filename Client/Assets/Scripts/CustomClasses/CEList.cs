using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class CEList<T>
{
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
    public void clear()
    {
        first = last = null;
    }
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
