using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[Serializable]
class CEList<T>
{
    CENode<T> first = null;
    CENode<T> last = null;
    public void push(T data)
    {
        if (first == null)
        {
            first = last = new CENode<T>(data);
        }
        else
        {
            CENode<T> x = new CENode<T>(data);
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

}
[Serializable]
public class CENode<T>
{
    public CENode<T> prev;
    public CENode<T> next;
    public T data;
    public CENode(T value)
    {
        data = value;
        prev = null;
        next = null;
    }
}
