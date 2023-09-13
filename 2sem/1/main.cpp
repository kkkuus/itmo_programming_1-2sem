#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include"geom.cpp"
#include"polynom.cpp"

int main()
{
    int n;
    std::cout << "Enter a count of points in polyline" << '\n';
    std::cin >> n;
    std::vector<Point> arr(n);
    double x, y;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x >> y;
        arr[i] = Point(x, y);
    }
    Polyline poly;
    poly = Polyline(n, arr);
    std::cout << poly.perimeter() << '\n';
    arr.resize(3);
    for (int i = 0; i < 3; ++i)
    {
        std::cin >> x >> y;
        arr[i] = Point(x, y);
    }
    Triangle tr;
    tr = Triangle(arr[0], arr[1], arr[2]);
    std::cout << tr.perimeter(arr[0], arr[1], arr[2]);

    return 0;


    int power;
    double number;
    std::cin >> number;
    /*std::cin >> power;
    std::vector<double> test(power + 1);
    for (int i = 0; i <= power; ++i)
    {
        std::cin >> test[i];
    }*/
    Polynom x1, y1;
    Polynom a, b, c;
    std::cin >> x1;
    std::cin >> y1;
    a = y1 + x1;
    b = x1 * number;
    c = x1 / number;
    std::cout << a << '\n' << b << '\n' << c;
    return 0;
}
