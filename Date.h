#ifndef BNAKACCOUNT_DATE_H
#define BNAKACCOUNT_DATE_H

#include <iostream>
#include <string>
#include <cmath>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Date{
private:
    int year;
    int month;
    int day;
    int totaldays;
public:
    Date(int year=1, int month=1, int day=1);
    ~Date();
    Date(const Date &d);

    int getYear() const{ return year;}
    int getMonth() const{ return month;}
    int getDay() const{ return day;}
    int getMaxDay() const;
    bool isLeapYear() const;
    void show() const;
    friend ostream & operator << (ostream &out,const Date &date);
    int distance() const;
    int operator - (const Date &d) const;
    bool operator < (const Date &d) const;
    static Date read(istringstream &str);
};


#endif //BNAKACCOUNT_DATE_H
