#include <iostream>

template <class T>
class CircularBuffer
{
private:
    int copacity;
    int begin;
    int end;
    T *buffer;
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        friend class CircularBuffer;
    private:
        T *it;
    public:
        Iterator()
        {}
        Iterator(T *temp) : it(temp)
        {}
        T &operator++(int)
        {
            return *it++;
        }
        T &operator--(int)
        {
            return *it--;
        }
        T &operator++()
        {
            return *++it;
        }
        T &operator--()
        {
             return *--it;
        }
        T &operator+(int n)
        {
            return *(it + n);
        }
        T &operator-(int n)
        {
            return *(it - n);
        }
        T &operator+=(int n)
        {
            return *(it + n);
        }
        T &operator-=(int n)
        {
            return *(it - n);
        }
        bool operator==(const Iterator &temp_iter)
        {
            return it == temp_iter.iter_cur;
        }
        bool operator!=(const Iterator &temp_iter)
        {
            return it != temp_iter.iter_cur;
        }
        bool operator>(const Iterator &temp_iter)
        {
            return it > temp_iter.iter_cur;
        }
        bool operator<(const Iterator &temp_iter)
        {
            return it < temp_iter.iter_cur;
        }
        bool operator>=(const Iterator &temp_iter)
        {
            return it >= temp_iter.iter_cur;
        }
        bool operator<=(const Iterator &temp_iter)
        {
            return it <= temp_iter.iter_cur;
        }
        T &operator*()
        {
            return *it;
        }
        T *operator->()
        {
            return it;
        }
        T &operator[](Iterator temp)
        {
            return *temp;
        }
    };

    CircularBuffer()
    {}

    CircularBuffer(int size)
    {
        copacity = size;
        buffer = new T[copacity];
        begin = 0;
        end = 0;
        for (int i = 0; i < copacity; ++i)
            buffer[i] = 0;
    }

    int size()
    {
        return copacity;
    }

    T &operator[](int i)
    {
        if (i < copacity)
            return buffer[i];
        else
            return buffer[0];
    }

    T &operator[](Iterator i)
    {
        return *i;
    }

    void push_back(T temp)
    {
        buffer[end] = temp;
        if (end + 1 < copacity)
            end = end + 1;
        else
            end = 0;
    }

    void pop_back()
    {
        if (end == 0)
            end = copacity - 1;
        else
            end = end - 1;
        buffer[end] = 0;
    }

    void push_front(T temp)
    {
        if (begin - 1 < 0)
            begin = copacity - 1;
        else
            begin = begin - 1;
        buffer[begin] = temp;
    }

    void pop_front()
    {
        buffer[begin] = 0;
        if (begin == copacity - 1)
            begin = 0;
        else
            begin = begin + 1;
    }

    void resize(int n)
    {
        T *new_buffer = new T[n];
        for (int i = 0; i < n; ++i)
        {
            if (i < copacity)
                new_buffer[i] = buffer[i];
            else
                new_buffer[i] = 0;
        }
        buffer = new_buffer;
        copacity = n;
    }
    Iterator begin_()
    {
        return Iterator(begin);
    }
    Iterator end_()
    {
        return Iterator(end);
    }
};


