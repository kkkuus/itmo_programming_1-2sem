#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

typedef struct
{
    int n[35];
    int size;
} uint1024_t;

typedef struct
{
    char s[310];
    int size;
} str;

str input;

uint1024_t from_uint(unsigned int x)
{
    uint1024_t y;
    for (int i = 0; i < 35; ++i)
        y.n[i] = 0;
    int i = 0;
    while (x > 0)
    {
        y.n[i] = x % 1000000000;
        x /= 1000000000;
        ++i;
    }
    y.size = i;
    return y;
}

void scanf_value(uint1024_t *x)
{
    for (int i = 0; i < 35; ++i)
        x->n[i] = 0;
    int temp[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int count_x = 0;
    int i = input.size - 1;
    int index_temp;
    while (i >= 0)
    {
        index_temp = 0;
        while (i >= 0 && index_temp < 9)
        {
            temp[index_temp] = (int)input.s[i] - 48;
            index_temp++;
            i--;
        }
        for (int k = 8; k > 0; --k)
        {
            x->n[count_x] += temp[k];
            x->n[count_x] *= 10;
        }
        x->n[count_x] += temp[0];
        for (int k = 0; k < 9; k++)
            temp[k] = 0;
        count_x++;
    }
    x->size = count_x;
}

void printf_value(uint1024_t x)
{
    printf("%d", x.n[x.size - 1]);
    int i = x.size - 2;
    while (i >= 0)
    {
        if (x.n[i] >= 100000000)
            printf("%d", x.n[i]);
        else
        {
            if (x.n[i] >= 10000000)
                printf("%s%d", "0", x.n[i]);
            else if (x.n[i] >= 1000000)
                printf("%s%d", "00", x.n[i]);
            else if (x.n[i] >= 100000)
                printf("%s%d", "000", x.n[i]);
            else if (x.n[i] >= 10000)
                printf("%s%d", "0000", x.n[i]);
            else if (x.n[i] >= 1000)
                printf("%s%d", "00000", x.n[i]);
            else if (x.n[i] >= 100)
                printf("%s%d", "000000", x.n[i]);
            else if (x.n[i] >= 10)
                printf("%s%d", "0000000", x.n[i]);
            else
                printf("%s%d", "00000000", x.n[i]);
        }
        --i;
    }
    printf("\n");
}

int compare(uint1024_t x, uint1024_t y)
{
    if (x.size != y.size)
    {
        if (x.size > y.size)
            return 1;
        if (x.size < y.size)
            return 0;
    }
    else
    {
        int i = x.size - 1;
        while (x.n[i] == y.n[i])
            i--;
        if (i < 0)
            return 1;
        else
        {
            if (x.n[i] > y.n[i])
                return 1;
            else
                return 0;
        }
    }
}

uint1024_t add_op(uint1024_t x, uint1024_t y)
{
    int buf = 0;
    for (int i = 0; i < y.size; ++i)
    {
        buf = x.n[i] + y.n[i];
        x.n[i] = buf % 1000000000;
        x.n[i + 1] += (buf / 1000000000);
    }
    int i = y.size;
    while (x.n[i] == 1000000000)
    {
        x.n[i] = 0;
        x.n[i + 1]++;
        ++i;
    }
    if (x.size == y.size && x.n[x.size] > 0)
        ++x.size;
    return x;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y)
{
    int occupy = 0;
    for (int i = 0; i < x.size; ++i)
    {
        x.n[i] += 1000000000 + occupy;
        if(i < y.size)
            x.n[i] -= y.n[i];
        if (x.n[i] >= 1000000000)
        {
            x.n[i] -= 1000000000;
            occupy = 0;
        }
        else occupy = -1;
    }
    int i = x.size - 1;
    while (i > 0 && x.n[i] == 0)
    {
        --i;
        --x.size;
    }
    return x;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y)
{
    uint1024_t mult;
    for (int i = 0; i < 35; ++i)
        mult.n[i] = 0;
    mult.size = x.size + y.size;
    long long int pr = 0;
    long long int buf;
    for (int i = 0; i < x.size; ++i)
    {
        for (int j = 0; j < y.size; ++j)
        {
            buf = (long long int)x.n[i] * (long long int)y.n[j] + pr;
            mult.n[i + j] += buf % 1000000000;
            pr = buf / 1000000000;
            pr += mult.n[i + j] / 1000000000;
            mult.n[i + j] %= 1000000000;
            if (j == y.size - 1)
            {
                mult.n[i + y.size] += pr;
                pr = 0;
            }
        }
    }
    if (pr > 0)
        mult.n[y.size + x.size - 1] = pr;
    if (mult.n[mult.size - 1] == 0)
        mult.size--;
    return mult;
}

void mult2(uint1024_t *x, int multiplier)
{
    int pr = 0;
    long long int buf;
    for (int i = 0; i < x->size; ++i)
    {
        buf = (long long int)x->n[i] * (long long int)multiplier + pr;
        x->n[i] = buf % 1000000000;
        pr = buf / 1000000000;
    }
    if (pr > 0)
    {
        x->size++;
        x->n[x->size - 1] = pr;
    }
}

uint1024_t degree_op(unsigned int d)
{
    if (d <= 31)
        return from_uint(pow(2, d));
    else
    {
        uint1024_t res = from_uint(pow(2, 31));
        d -= 31;
        while (d > 0)
        {
            mult2(&res, 2);
            d--;
        }
        return res;
    }
}

uint1024_t factorial_op(unsigned int d)
{
    unsigned int temp = 2, temp_res = 1;

    if (d == 0 || d == 1)
        return from_uint(1);
    while (temp <= d && temp <= 7)
    {
        temp_res *= temp;
        if (temp == d)
            return from_uint(temp_res);
        temp++;
    }
    uint1024_t res = from_uint(temp_res);
    while (temp <= d)
    {
        mult2(&res, temp);
        ++temp;
    }
    return res;
}

unsigned int rem = 0;
uint1024_t division_op(uint1024_t x, unsigned int d)
{
    uint1024_t res_temp;
    res_temp.size = 0;
    if (x.size == 1)
    {
        res_temp.size++;
        rem = x.n[0] % d;
        res_temp.n[0] = x.n[0] / d;
        return res_temp;
    }
    long long int buf = 0;
    for (int i = x.size - 1; i > 0; --i)
    {
        if (x.n[i] >= d)
            buf = (long long int)x.n[i] * 1000000000;
        else
            buf = (long long int)x.n[i] * 1000000000 + (long long int)x.n[i - 1];
        res_temp.n[res_temp.size] = buf / d;
        res_temp.size++;
        x.n[i - 1] = buf % d;
    }
    rem = x.n[0];
    uint1024_t res;
    res.size = res_temp.size;
    for (int i = 0; i < res_temp.size; ++i)
    {
        res.n[i] = res_temp.n[res_temp.size - i - 1];
    }
    return res;
}

int main()
{
    printf("Enter a short number: ");
    unsigned int number;
    scanf("%u", &number);
    uint1024_t short_n;
    short_n = from_uint(number);
    printf("Short number is: ");
    printf_value(short_n);

    uint1024_t x, y, sum, sub, mult;

    printf("Enter the first long number: ");
    scanf("%s", input.s);
    input.size = (int)strlen(input.s);
    if (input.size >= 309)
    {
        printf("Undefined Behavior\n");
        return -1;
    }
    scanf_value(&x);
    printf("   The first long number is: ");
    printf_value(x);

    printf("Enter the second long number: ");
    scanf("%s", input.s);
    input.size = (int)strlen(input.s);
    if (input.size >= 309)
    {
        printf("Undefined Behavior\n");
        return -1;
    }
    scanf_value(&y);
    printf("   The second long number is: ");
    printf_value(y);

    sum = add_op(x, y);
    printf("Sum of numbers: ");
    printf_value(sum);


    //printf("%d\n", compare(x, y));
    if(compare(x, y) == 0)
        printf("Subtract of numbers: The result is negative\n");
    else
    {
        sub = subtr_op(x, y);
        printf("Subtract of numbers: ");
        printf_value(sub);
    }

    if(x.size + y.size > 128)
        printf("Multiplication of numbers: Overflow of the result\n");
    if (compare(x, y) == 0)
        mult = mult_op(y, x);
    else
        mult = mult_op(x, y);
    printf("Multiplication of numbers: ");
    printf_value(mult);

    printf("The result of raising 2 to the power of %u: ", number);
    if (number > 1024)
        printf("We can't perform the operation yet - the number is too large\n");
    else
    {
        uint1024_t degree;
        degree = degree_op(number);
        printf_value(degree);
    }

    printf("The result of taking the factorial of the number %u: ", number);
    if (number > 170)
        printf("We can't perform the operation yet - the number is too large\n");
    else
    {
        uint1024_t factorial;
        factorial = factorial_op(number);
        printf_value(factorial);
    }

    printf("The quotient of dividing a long number by %u: ", number);
    if (number > 2147483647)
        printf("We can't perform the operation yet - the number is too large\n");
    else
    {
        uint1024_t division;
        division = division_op(x, number);
        printf_value(division);
        printf("The remainder of dividing a long number by %u: %u\n", number, rem);
    }
    int kl;
    scanf("%d", &kl);
}
