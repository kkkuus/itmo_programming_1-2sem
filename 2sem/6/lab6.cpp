#include <iostream>
#include <vector>

template<const int power>
class Polynom
{
private:
    int coef[power + 1];
    const int temp_it = 0;
public:

    constexpr int Power()
    {
        return power;
    }
    constexpr int Coef(const int i) const
    {
        return coef[i];
    }
    constexpr Polynom()
    {}

    constexpr Polynom(const int data[])
    {
        init(data, power);
    }
    constexpr void init(const int data[], const int degree)
    {
        if (degree < 0)
            return;
        else
        {
            coef[degree] = data[degree];
            init(data, degree - 1);
        }
    }
    constexpr int pow(const int x, const int degree)const
    {
        if (degree == 0)
            return 1;
        else
            return x * pow(x, degree - 1);
    }
    constexpr int value_point(const int x, const int degree)const
    {
        if (degree == 0)
            return coef[0];
        else
            return coef[degree] * pow(x, degree) + value_point(x, degree - 1);

    }

    friend std::ostream& operator<<(std::ostream& stream, Polynom data)
    {
        for (int i = 0; i <= data.power; ++i)
            stream << data.coef(i) << ' ';
        return stream;
    }
    constexpr void push(const int i)
    {
        coef[temp_it] = i;
        temp_it++;
    }
};

/*int main()
{
    constexpr const int arr[3] = { 1, 2, 3 };
    constexpr const int x = 4;
    constexpr Polynom<2> p(arr);
    constexpr int res = p.value_point(x, 2);
    static_assert(res == 57);
    std::cout << res;
}*/