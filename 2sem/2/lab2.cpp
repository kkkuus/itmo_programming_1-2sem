#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
//#define CURL_STATICLIB
#include<curl/curl.h>
//#include "C:\curl-7.82.0\include\curl\curl.h"
#include "json-develop\single_include\nlohmann\json.hpp"
#include<conio.h>
#include<string>
using json = nlohmann::json;

struct Valute
{
    std::vector<double> val;
    std::string name;
};

double average(Valute& v)
{
    double sum = 0;
    for (int i = 0; i < v.val.size(); ++i)
        sum += v.val[i];
    return sum / v.val.size();
}

double median(Valute& v)
{
    std::sort(v.val.begin(), v.val.end());
    int index = v.val.size();
    if (index % 2 == 1)
        return v.val[(index - 1) / 2];
    else
        return (v.val[index / 2 - 1] + v.val[index / 2]) / 2;
}

struct All_valutes
{
    std::vector<Valute> val_name;
    int flag;
} ;

void print_stat(All_valutes& v)
{
    for (int i = 0; i < v.val_name.size(); ++i)
    {
        std::cout << v.val_name[i].name << "  median - " << median(v.val_name[i])
            << " average - " << average(v.val_name[i]) << std::endl;
    }
}

All_valutes kurs;

static size_t write_data(char *ptr, size_t size, size_t nmemb, std::string* data)
{
    if (data)
    {
        data->append(ptr, size*nmemb);
        return size*nmemb;
    }
    else
        return 0;
}

void print()
{
    CURL *curl = curl_easy_init();
    CURLcode res;
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "www.cbr-xml-daily.ru/daily_json.js");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        auto j = json::parse(readBuffer);
        int i = 0;
        for (auto& iter : j["Valute"])
        {
            std::cout << iter["CharCode"] << "  "<< iter["Value"] <<'\n';
            if (kurs.flag == 0)
            {
                Valute new_valute;
                new_valute.name = iter["CharCode"];
                kurs.val_name.push_back(new_valute);
            }
            kurs.val_name[i].val.push_back(iter["Value"]);
            ++i;
        }
        kurs.flag = 1;
    }
}
int main()
{
    while (!kbhit())
    {
        print();
        Sleep(10000);
    }
    print_stat(kurs);
    return 0;
}
