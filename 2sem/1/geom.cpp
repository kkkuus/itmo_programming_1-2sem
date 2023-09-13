#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

class Point
{
private:
    double x_;
    double y_;

public :
    double x() const
    {
        return x_;
    }
    double y() const
    {
        return y_;
    }

    Point(double new_x = 0, double new_y = 0) :
        x_(new_x), y_(new_y)
    {}

    Point(const Point& new_point) :
        x_(new_point.x_), y_(new_point.y_)
    {}

    ~Point()
    {}

    Point& operator=(const Point& other)
    {
        if (&other == this)
            return *this;
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
    Point vector(const Point& begin, const Point& end);
};

double length(Point begin, Point end)
{
    return sqrt(pow((end.x() - begin.x()), 2) + pow((end.y() - begin.y()), 2));
}

double multi_vect(Point a, Point b)
{
    return a.x() * b.y() - a.y() * b.x();
}

Point Point::vector(const Point& begin, const Point& end)
{
    Point v;
    double v_x, v_y;
    v_x = end.x() - begin.x();
    v_y = end.y() - begin.y();
    v = Point(v_x, v_y);
    return v;
}



class Polyline
{
protected:
    int count_point_;
    std::vector<Point> points_;

public:
    int count_point() const
    {
        return count_point_;
    }

    Point points(int i) const
    {
        return points_[i];
    }

    Polyline(int new_count = 0, std::vector<Point> data = {}) :
        count_point_(new_count), points_(data)
    {}

    Polyline(const Polyline& copy_polyline) :
        count_point_(copy_polyline.count_point_), points_(copy_polyline.points_)
    {}

    ~Polyline()
    {}

    Polyline& operator=(const Polyline& other)
    {
        if (&other == this)
            return *this;
        count_point_ = other.count_point_;
        points_ = other.points_;
        return *this;
    }

    double perimeter();
    void add_point(const Point& point);
};

double Polyline::perimeter()
{
    double per = 0;
    for (int i = 1; i < points_.size(); ++i)
        per = per + sqrt(pow((points_[i].x() - points_[i - 1].x()), 2) + pow((points_[i].y() - points_[i - 1].y()), 2));
    return per;
}

void Polyline::add_point(const Point& point)
{
    points_.push_back(point);
    ++count_point_;
}

class Closed_polyline : public Polyline
{
public:
    Closed_polyline(int new_count = 0, std::vector<Point> data = {}) :
        Polyline(new_count, data)
    {
        try
        {
            if (count_point_ != 0 && data.size() - 1 != new_count)
                throw -1;
        }
        catch(int)
        {
            std::cout << "its not a closed polyline";
            exit(-1);
        }
    }
    Closed_polyline(const Closed_polyline& copy_closed_polyline) :
        Polyline(copy_closed_polyline)
    {}
    ~Closed_polyline()
    {}

    Closed_polyline &operator=(const Closed_polyline &other)
    {
        if (&other == this)
            return *this;
        count_point_ = other.count_point_;
        points_ = other.points_;
        return *this;
    }
};

bool sign(Point o, Point a, Point b)
{
    if (((a.x() - o.x()) * (b.y() - o.y()) - (a.y() - o.y()) * (b.x() - o.x())) < 0)
        return 0;
    else
        return 1;
}
class Polygon : public Closed_polyline
{
public:
    Polygon(int new_count = 0, std::vector<Point> data = {}) :
        Closed_polyline(new_count, data)
    {
        bool pz = sign(data[1], data[0], data[2]);
        for (int i = 0; i < new_count - 2; ++i)
        {
            bool nz = sign(data[i + 1], data[i], data[i + 2]);
            try
            {
                if (nz != pz)
                    throw -1;
            }
            catch(int)
            {
                std::cout << "this polygon is not convex";
                exit(-1);
            }
        }
    }
    Polygon(const Polygon& copy_polygon) :
        Closed_polyline(copy_polygon)
    {}
    ~Polygon()
    {}
    Polygon &operator=(const Polygon& other)
    {
        if (&other == this)
            return *this;
        count_point_ = other.count_point_;
        points_ = other.points_;
    }
    double square();
};

double Polygon::square()
{
    double s = 0;
    Point begin, end;
    for (int i = 1; i < count_point_ - 1; ++i)
    {
        begin.vector(points(0), points(i));
        end.vector(points(0), points(i + 1));
        s = s + (begin.x() * end.y() - begin.y() * end.x()) / 2;
    }
    return std::abs(s);
}


class Triangle
{
private:
    Point a, b, c;
public:
    Point get_a() const
    {
        return a;
    }

    Point get_b() const
    {
        return b;
    }

    Point get_c() const
    {
        return c;
    }

    Triangle(Point new_a = {0, 0}, Point new_b = {0, 1}, Point new_c = {1, 0}) :
        a(new_a), b(new_b), c(new_c)
    {}

    Triangle(const Triangle& copy_triangle) :
        a(copy_triangle.a), b(copy_triangle.b), c(copy_triangle.c)
    {}

    ~Triangle()
    {}

    Triangle& operator=(const Triangle& other)
    {
        if (&other == this)
            return *this;
        a = other.a;
        b = other.b;
        c = other.c;
        return *this;
    }

    double perimeter(const Point& a, const Point& b, const Point& c);
    double square(const Point& a, const Point& b, const Point & c);
};

double Triangle::perimeter(const Point& a, const Point& b, const Point& c)
{
    return length(a, b) + length(a, c) + length(b, c);
}

double Triangle::square(const Point& a, const Point& b, const Point& c)
{
    Point temp1, temp2;
    temp1.vector(a, b);
    temp2.vector(a, c);
    return abs(multi_vect(temp1, temp2) / 2);
}

class Trapezoid
{
private:
    std::vector<Point> points_;
public:
    Point points(int i) const
    {
        return points_[i];
    }

    Trapezoid(std::vector<Point> data = {0, 0, 1, 0, 0, 1, 1, 1}) :
        points_(data)
    {
        try
        {
            if(data.size() != 4)
                throw -1;
        }
        catch(int)
        {
            std::cout << "this not a trapezoid";
            exit(-1);
        }
        Point temp1, temp2;
        temp1.vector(data[0], data[1]);
        temp2.vector(data[2], data[3]);
        try
        {
            if (multi_vect(temp1, temp2) == 0)
                throw -1;
        }
        catch(int)
        {
            std::cout << "this not a trapezoid";
            exit(-1);
        }
    }

    Trapezoid(const Trapezoid& copy_trapezoid) :
        points_(copy_trapezoid.points_)
    {}

    ~Trapezoid()
    {}

    Trapezoid& operator=(const Trapezoid& other)
    {
        if (&other == this)
            return *this;
        points_ = other.points_;
        return *this;
    }

    double perimeter();
    double square();
};

double Trapezoid::perimeter()
{
    double p = 0;
    p += length(points(0), points(1)) + length(points(1), points(2));
    p += length(points(2), points(3)) + length(points(3), points(0));
    return p;
}

double Trapezoid::square()
{
    Point temp1, temp2, temp3;
    temp1.vector(points(0), points(2));
    temp2.vector(points(0), points(3));
    temp3.vector(points(0), points(1));
    return (abs(multi_vect(temp1, temp2) / 2) + abs(multi_vect(temp2, temp3) / 2));

}

class Regular_polygon
{
private:
    Point o;
    int count;
    double r;
public:
    Point center()
    {
        return o;
    }
    int points()
    {
        return count;
    }
    double radix()
    {
        return r;
    }

    Regular_polygon(Point new_o = {0, 0}, int new_count = 0, double new_r = 0) :
        o(new_o), count(new_count), r(new_r)
    {}

    Regular_polygon(const Regular_polygon& copy_poly) :
        o(copy_poly.o), count(copy_poly.count), r(copy_poly.r)
    {}

    ~Regular_polygon()
    {}
    Regular_polygon& operator=(const Regular_polygon& other)
    {
        if (&other == this)
            return *this;
        o = other.o;
        count = other.count;
        r = other.r;
    }

    double side_length();
    double perimeter();
    double square();
};

double Regular_polygon::side_length()
{
    double pi = 3.1415;
    double alpha = 2*pi / count;
    return sqrt(2*r*r - 2*r*r*cos(alpha));
}

double Regular_polygon::perimeter()
{
    return count * side_length();
}

double Regular_polygon::square()
{
    return perimeter() * r / 2;
}

