#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int count_request = 0;
int count_time = 0;
struct tm local_time(char s[20])
{
    int i = 0;
    struct tm time;
    time.tm_mday = ((int)s[i] - 48) * 10 + (int)s[i + 1] - 48;
    i += 3;
    if (s[i] == 'J' && s[i + 1] == 'a' && s[i + 2] == 'n')
        time.tm_mon = 0;
    else if (s[i] == 'F' && s[i + 1] == 'e' && s[i + 2] == 'b')
        time.tm_mon = 1;
    else if (s[i] == 'M' && s[i + 1] == 'a' && s[i + 2] == 'r')
        time.tm_mon = 2;
    else if (s[i] == 'A' && s[i + 1] == 'p' && s[i + 2] == 'r')
        time.tm_mon = 3;
    else if (s[i] == 'M' && s[i + 1] == 'a' && s[i + 2] == 'y')
        time.tm_mon = 4;
    else if (s[i] == 'J' && s[i + 1] == 'u' && s[i + 2] == 'n')
        time.tm_mon = 5;
    else if (s[i] == 'J' && s[i + 1] == 'u' && s[i + 2] == 'l')
        time.tm_mon = 6;
    else if (s[i] == 'A' && s[i + 1] == 'u' && s[i + 2] == 'g')
        time.tm_mon = 7;
    else if (s[i] == 'S' && s[i + 1] == 'e' && s[i + 2] == 'p')
        time.tm_mon = 8;
    else if (s[i] == 'O' && s[i + 1] == 'c' && s[i + 2] == 't')
        time.tm_mon = 9;
    else if (s[i] == 'N' && s[i + 1] == 'o' && s[i + 2] == 'v')
        time.tm_mon = 10;
    else if (s[i] == 'D' && s[i + 1] == 'e' && s[i + 2] == 'c')
        time.tm_mon = 11;
    i += 4;
    time.tm_year = 1000 * ((int)s[i] - 48) + 100 * ((int)s[i + 1] - 48) + 10 * ((int)s[i + 2] - 48) + (int)s[i + 3] - 48;
    time.tm_year -= 1900;
    i += 5;
    time.tm_hour = 10 * ((int)s[i] - 48) + (int)s[i + 1] - 48;
    i += 3;
    time.tm_min = 10 * ((int)s[i] - 48) + (int)s[i + 1] - 48;
    i += 3;
    time.tm_sec = 10 * ((int)s[i] - 48) + (int)s[i + 1] - 48;
    return time;
};

typedef struct
{
    char str_time[20];
    time_t int_time;
    int count_req;
} parse_time;

parse_time time_arr[2000000];

void error(char str[500], int size)
{
    char request[500];
    char trans_time[20];
    int i = 0, j = 0;
    while (i < size && str[i] != '[')
        ++i;
    ++i;
    while (i < size && j < 20)
    {
        trans_time[j] = str[i];
        ++i;
        ++j;
    } 
    j = 0;
    time_arr[count_time].count_req = 0;
    if (count_time > 0 && strcmp(trans_time, time_arr[count_time - 1].str_time) == 0)
        ++time_arr[count_time - 1].count_req;
    else
    {
        strcpy(time_arr[count_time].str_time, trans_time);
        struct tm temp_st = local_time(time_arr[count_time].str_time);
        time_arr[count_time].int_time = mktime(&temp_st);
        ++time_arr[count_time].count_req;
        ++count_time;
    }
    
    while (i < size && str[i] != '"')
        ++i;
    ++i;
    while (i < size && str[i] != '"')
    {
        request[j] = str[i];
        ++i;
        ++j;
    } 
    if (i + 2 < size && str[i + 1] == ' ' && str[i + 2] == '5')
    {
        count_request++;
        printf("%d) ", count_request);
        for (int k = 0; k < j; ++k)
            printf("%c", request[k]);
        printf("\n");
    }
}

int max_window = 0, max_index1 = 0, max_index2 = 0;
void time_window(int param_time)
{
    int temp_sum;
    int j = 0;
    for (int i = 0; i < count_time; ++i)
    {
        temp_sum = 0;
        j = i;
        while (j < count_time && difftime(time_arr[j].int_time, time_arr[i].int_time) < param_time)
        {
            temp_sum += time_arr[j].count_req;
            ++j;
        }
        if (temp_sum > max_window)
        {
            max_window = temp_sum;
            max_index1 = i;
            max_index2 = j - 1;
        }

    }
}

int main()
{
    int param_time;
    FILE *file;
    file = fopen("access_log_Jul95", "r");
    //file = fopen("input", "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    char symbol;
    char str[500];
    count_time = 0;
    printf("List of requests:\n");
    while ((symbol = fgetc(file)) != EOF)
    {
        int j = 0;
        while (symbol != EOF && symbol != '\n')
        {
            str[j] = symbol;
            ++j;
            symbol = fgetc(file);
        }
        error(str, j);
    }
    printf("Number of requests with error 5xx: %d\n", count_request);
    printf("Enter the duration of the time window in seconds: ");

    scanf("%d", &param_time);
    time_window(param_time);
    printf("A time window lasting %d seconds when the number of requests was maximum: \n", param_time);
    printf("%s\n", time_arr[max_index1].str_time);
    printf("%s\n", time_arr[max_index2 + 1].str_time);
    printf("The number of requests during this period: %d\n", max_window);
    
}