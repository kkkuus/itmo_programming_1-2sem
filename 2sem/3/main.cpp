#include <iostream>
#include <vector>
#include "buff.cpp"
#include "algo.cpp"

template<typename T>
bool f(T x)
{
    return x > 0;
}

template<typename T>
bool greater(T x, T y)
{
    return x > y;
}

template<typename T>
bool f2(T x, T y)
{
    return x == y;
}

template<typename T>
bool f3(T x, T y)
{
    return x == y;
}
struct point
{
    int x, y;
};

bool fp(point x)
{
    return x.x * x.y > 0;
}
bool greaterp(point x, point y)
{
    return x.x * x.y > y.x * y.y;
}
bool f2p(point x, point y)
{
    return x.x * x.y == y.x * y.y;
}
bool f3p(point x, point y)
{
    return x.x == y.x && x.y == y.y;
}

int main()
{
    std::cout << "---Tests for buffe---" << std::endl;
    CircularBuffer<int> arr(7);
    std::cout << arr.size() << std::endl;
    arr.push_back(5);
    arr.push_back(4);
    arr.push_back(8);
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
    arr.resize(4);
    arr.push_front(2);
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
    arr.push_back(1);
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
    arr.pop_back();
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;


    std::cout << "---Test for algorithms(for vector)---" << std::endl;
    std::vector<int> v(4);
    for (int i = 0; i < 4; ++i)
        v[i] = i + 1;
    std::cout << "all_of          " << all_of(v.begin(), v.end(), f<int>) << std::endl;
    std::cout << "any_of          " << any_of(v.begin(), v.end(), f<int>) << std::endl;
    std::cout << "none_of         " << none_of(v.begin(), v.end(), f<int>) << std::endl;
    std::cout << "one_of          " << one_of(v.begin(), v.end(), f<int>) << std::endl;
    std::cout << "is_sorted       " << is_sorted(v.begin(), v.end(), greater<int>) << std::endl;
    std::cout << "is_partitioned  " << is_partitioned(v.begin(), v.end(), f<int>) << std::endl;
    std::cout << "find_not        " << *find_not(v.begin(), v.end(), 3, f3<int>) << std::endl;
    std::cout << "find_backward   " << *find_backward(v.begin(), v.end(), 3, f3<int>) << std::endl;
    std::cout << "is_palindrome   " << is_palindrome(v.begin(), v.end(), f2<int>) << std::endl;


    std::cout << "---Test for algorithms(for other types)---" << std::endl;
    std::vector<point> p(4);
    for (int i = 0; i < 4; ++i)
    {
        p[i].x = i;
        p[i].y = 4 - i;
    }
    point t1 = {2, 1};
    point t2 = {3, 1};
    std::cout << "all_of          " << all_of(p.begin(), p.end(), fp) << std::endl;
    std::cout << "any_of          " << any_of(p.begin(), p.end(), fp) << std::endl;
    std::cout << "none_of         " << none_of(p.begin(), p.end(), fp) << std::endl;
    std::cout << "one_of          " << one_of(p.begin(), p.end(), fp) << std::endl;
    std::cout << "is_sorted       " << is_sorted(p.begin(), p.end(), greaterp) << std::endl;
    std::cout << "is_partitioned  " << is_partitioned(p.begin(), p.end(), fp) << std::endl;
    std::cout << "find_not        " << find_not(p.begin(), p.end(), t1, f3p)->x << std::endl;
    std::cout << "find_backward   " << find_backward(p.begin(), p.end(), t2, f3p)->x << std::endl;
    std::cout << "is_palindrome   " << is_palindrome(p.begin(), p.end(), f2p) << std::endl;

}

