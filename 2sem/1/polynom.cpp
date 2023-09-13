#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

class Polynom
{
private:
    int power_;
    std::vector<double> coef_;
public:
    int power() const
    {
        return power_;
    }
    double coef(int i) const
    {
        return coef_[i];
    }

    Polynom(int t_power = 0, std::vector<double> data = {}) :
        power_(t_power), coef_(data)
    {}


    Polynom(const Polynom& copy_polynom) :
        power_(copy_polynom.power_), coef_(copy_polynom.coef_)
    {}

    ~Polynom()
    {}

    Polynom& operator=(const Polynom& other)
    {
        if (&other == this)
            return *this;
        power_ = other.power_;
        coef_ = other.coef_;
        return *this;
    }


    Polynom& operator--()
    {
        for (int i = 0; i <= power_; ++i)
            coef_[i] = (-1) * coef_[i];
        return *this;
    }

    Polynom operator+=(const Polynom& sum)
    {
        if (sum.power_ > power_)
        {
            power_ = sum.power_;
            coef_.resize(power_ + 1);
        }
        for (int i = 0; i <= sum.power_; ++i)
            coef_[i] = coef_[i] + sum.coef_[i];
        return *this;
    }

    Polynom operator-=(const Polynom& ded)
    {
        if (ded.power_ > power_)
        {
            power_ = ded.power_;
            coef_.resize(power_ + 1);
        }
        for (int i = 0; i <= ded.power_; ++i)
            coef_[i] = coef_[i] - ded.coef_[i];
        return *this;
    }

    Polynom operator*=(const double& number)
    {
        for (int i = 0; i < power_; ++i)
            coef_[i] = number * coef_[i];
        return *this;
    }

    Polynom operator/=(const double& number)
    {
        try
        {
            if (number == 0)
                throw -1;
        }
        catch(int)
        {
            std::cout << "enter another number";
            exit(-1);
        }
        for (int i = 0; i < power_; ++i)
            coef_[i] = coef_[i] / number;
        return *this;
    }

    double operator[](int index)
    {
        try
        {
            if (index < 0 || index > power_)
                throw -1;
        }
        catch(int)
        {
            std::cout << "invalid index";
            exit(-1);
        }
        return this->coef_[index];
    }

};

std::istream& operator>>(std::istream& stream, Polynom& data)
{
    std::cout << "Enter the degree of the polynomial" << '\n';
    int in_power;
    double temp;
    std::cin >> in_power;
    std::cout << "Enter the coefficients of the polynomial starting from the free term" << '\n';
    std::vector<double> data_coef(in_power + 1);
    for (int i = 0; i <= in_power; ++i)
        std::cin >> data_coef[i];
    data = Polynom(in_power, data_coef);
    return stream;
}

std::ostream& operator<<(std::ostream &stream, const Polynom &data)
{
    for (int i = 0; i <= data.power(); ++i)
        stream << data.coef(i) << ' ';
    return stream;
}

bool operator==(const Polynom& poly1, const Polynom& poly2)
{
    if (poly1.power() != poly2.power())
        return false;
    else
    {
        for (int i = 0; i <= poly1.power(); ++i)
        {
            if (poly1.coef(i) != poly2.coef(i))
                return false;
        }
        return true;
    }
}

bool operator!=(const Polynom& poly1, const Polynom& poly2)
{
    return !operator==(poly1, poly2);
}

Polynom operator+(const Polynom& sum1, const Polynom& sum2)
{
    Polynom res;
    bool max_poly;
    int res_power;
    if (sum1.power() >= sum2.power())
    {
        max_poly = 0;
        res_power = sum1.power();
    }
    else
    {
        max_poly = 1;
        res_power = sum2.power();
    }
    int temp = std::min(sum1.power(), sum2.power());
    std::vector<double> res_coef(res_power + 1);
    for (int i = 0; i <= temp; ++i)
        res_coef[i] = sum1.coef(i) + sum2.coef(i);
    if (max_poly == 0)
    {
        for (int i = temp + 1; i <= res_power; ++i)
            res_coef[i] = sum1.coef(i);
    }
    else
    {
        for (int i = temp + 1; i <= res_power; ++i)
            res_coef[i] = sum2.coef(i);
    }
    res = Polynom(res_power, res_coef);
    return res;
}

Polynom operator-(const Polynom& reduced, const Polynom& deductible)
{
    Polynom difference;
    bool max_poly;
    int difference_power;
    if (reduced.power() >= deductible.power())
    {
        max_poly = 0;
        difference_power = reduced.power();
    }
    else
    {
        max_poly = 1;
        difference_power = deductible.power();
    }
    std::vector<double> difference_coef(difference_power + 1);
    if (max_poly == 0)
    {
        for (int i = 0; i <= deductible.power(); ++i)
            difference_coef[i] = reduced.coef(i) - deductible.coef(i);
        for (int i = deductible.power() + 1; i <= difference_power; ++i)
            difference_coef[i] = reduced.coef(i);
    }
    else
    {
        for (int i = 0; i <= reduced.power(); ++i)
            difference_coef[i] = reduced.coef(i) - deductible.coef(i);
        for (int i = reduced.power() + 1; i <= difference_power; ++i)
            difference_coef[i] = (-1) * deductible.coef(i);
    }
    difference = Polynom(difference_power, difference_coef);
    return difference;
}


Polynom operator*(const Polynom& data, const double& number)
{
    Polynom poly;
    int poly_power = data.power();
    std::vector<double> poly_coef(poly_power + 1);
    for (int i = 0; i <= poly_power; ++i)
        poly_coef[i] = data.coef(i) * number;
    poly = Polynom(poly_power, poly_coef);
    return poly;
}

Polynom operator/(const Polynom& data, const double& number)
{
    try
    {
        if (number == 0)
            throw -1;
    }
    catch(int)
    {
        std::cout << "enter another number";
        exit(-1);
    }
    Polynom poly;
    int poly_power = data.power();
    std::vector<double> poly_coef(poly_power + 1);
    for (int i = 0; i <= poly_power; ++i)
        poly_coef[i] = data.coef(i) / number;
    poly = Polynom(poly_power, poly_coef);
    return poly;
}

