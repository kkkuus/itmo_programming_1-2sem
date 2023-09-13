

template <class Iterator, class P>
bool all_of(Iterator begin, Iterator end, P predicate)
{
    while (begin != end)
    {
        if (!predicate(*begin))
            return false;
        ++begin;
    }
    return true;
}

template <class Iterator, class P>
bool any_of(Iterator begin, Iterator end, P predicate)
{
    while (begin != end)
    {
        if (predicate(*begin))
            return true;
        ++begin;
    }
    return false;
}

template <class Iterator, class P>
bool none_of(Iterator begin, Iterator end, P predicate)
{
    while (begin != end)
    {
        if (predicate(*begin))
            return false;
        ++begin;
    }
    return true;
}

template <class Iterator, class P>
bool one_of(Iterator begin, Iterator end, P predicate)
{
    int count = 0;
    while (begin != end)
    {
        if (predicate(*begin))
            ++count;
        if (count > 1)
            return false;
        ++begin;
    }
    if (count == 1)
        return true;
    else
        return false;
}

template <class Iterator, class P>
bool is_sorted(Iterator begin, Iterator end, P predicate)
{
    auto cur = begin;
    ++cur;
    while (cur != end)
    {
        if (!predicate(*cur, *begin))
            return false;
        ++begin;
        ++cur;
    }
    return true;
}

template <class Iterator, class P>
bool is_partitioned(Iterator begin, Iterator end, P predicate)
{
    while (begin != end)
    {
        if (!predicate(*begin))
            break;
        ++begin;
    }
    if (begin == end)
        return false;
    while (begin != end)
    {
        if (predicate(*begin))
            return false;
        ++begin;
    }
    return true;
}

template <class Iterator, class T, class P>
Iterator find_not(Iterator begin, Iterator end, T temp, P predicate)
{
    while (begin != end)
    {
        if (!predicate(*begin, temp))
            return begin;
        ++begin;
    }
    return end;
}

template <class Iterator, class T, class P>
Iterator find_backward(Iterator begin, Iterator end, T temp, P predicate)
{
    Iterator cur = end;
    --cur;
    while (cur >= begin)
    {
        if (predicate(*cur, temp))
            return cur;
        --cur;
    }
    return end;
}

template <class Iterator, class P>
bool is_palindrome(Iterator begin, Iterator end, P predicate)
{
    --end;
    while (begin < end)
    {
        if (!predicate(*begin, *end))
            return false;
        ++begin;
        --end;
    }
    return true;
}

