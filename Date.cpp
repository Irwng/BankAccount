#include "Date.h"

namespace {//namespace使下面的定义只在当前文件中有效
    const int DATS_BEFORE_MONTH[]={0,31,59,90,120,151,181,
                                   212,243,273,304,334,365};
    //存储平年中的某个月1日之前有多少天，为便于getMaxDay函数的实现，该函数多出一项
}

Date::Date(int year, int month, int day):year(year),month(month),day(day){
    if(day<=0||day>getMaxDay())
        throw runtime_error("Invalid date");
}

Date::~Date() {
//    cout<<"Destructing..."<<endl;
}

Date::Date(const Date &d):year(d.year),month(d.month),day(d.day){
//    cout<<"Copying..."<<endl;
}

int Date::getMaxDay() const {
    if(isLeapYear()&&month==2)
        return 29;
    return DATS_BEFORE_MONTH[month]-DATS_BEFORE_MONTH[month-1];
}

bool Date::isLeapYear() const {
    return (((year % 4) == 0) && ((year % 100 != 0))) || ((year % 400) == 0);
}

int Date::distance() const {
    int years = year-2008;
    int totaldays = years*365+years/4-years/100+years/400+DATS_BEFORE_MONTH[month-1]+day;
    if(isLeapYear()&&month>2) totaldays++;
    return totaldays;
}

void Date::show() const {
    cout<<year<<"-"<<month<<"-"<<day;
}

int Date::operator - (const Date &d) const {
    return this->distance()-d.distance();
}

bool Date::operator < (const Date &d) const{
    return (year<d.year)||((year==d.year)&&(month<d.month))||
            ((year==d.year)&&(month==d.month)&&(day<d.day));
}

Date Date::read(istringstream &str){
    int year;
    str>>year;
    int month;
    str>>month;
    int day;
    str>>day;
    Date date(year,month,day);
    return date;
}

ostream & operator << (ostream &out,const Date & date){
    out<<date.year<<"-"<<date.month<<"-"<<date.day;
    return out;
}