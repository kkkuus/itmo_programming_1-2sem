#include "pch.h"
#include "C:\Users\Elizaveta\Desktop\Proga\Sem2\6_2\lab6\lab6\lab6.cpp"

TEST(Lab_test, T1)
{
    constexpr const int arr[3] = { 1, 2, 3 };
    constexpr const int x = 4;
    constexpr Polynom<2> p(arr);
    constexpr int res = p.value_point(x, 2);
    static_assert(res == 57, "TRUE");
    EXPECT_EQ(res, 57);
}

TEST(Lab_test, T2)
{
    constexpr const int arr[3] = { 1, 2, 3 };
    constexpr const int x = 0;
    constexpr Polynom<2> p(arr);
    constexpr int res = p.value_point(x, 2);
    static_assert(res == 1, "TRUE");
    EXPECT_EQ(res, 0);
}

TEST(Lab_test, T3)
{
    constexpr const int arr[2] = { 0, 0 };
    constexpr const int x = 0;
    constexpr Polynom<1> p(arr);
    constexpr int res = p.value_point(x, 1);
    static_assert(res == 0, "TRUE");
    EXPECT_EQ(res, 0);
}

TEST(Lab_test, T4)
{
    constexpr const int arr[4] = { 1, 1, 1, 1 };
    constexpr const int x = 2;
    constexpr Polynom<3> p(arr);
    constexpr int res = p.value_point(x, 3);
    static_assert(res == 15, "TRUE");
    EXPECT_EQ(res, 0);
}
