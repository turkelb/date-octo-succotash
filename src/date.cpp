#include <iostream>
#include <sstream>
#include "date.hpp"

/*
project::Date::Date() {
    this->mday = 01;
    this->mmonth = 01;
    this->myear = 1900;
}
*/

project::Date::Date(int d, int m, int y) {
    this->mday = d;
    this->mmonth = m;
    this->myear = y;
}

project::Date::Date(const char *p) {
    //Format: gg/aa/yil
    std::stringstream s;
    s << p;
    int a,b,c; //to store the 4 ints
    char ch; //to temporarily store the '.'
    s >> a >> ch >> b >> ch >> c;

    this->mday = a;
    this->mmonth = b;
    this->myear = c;
}

project::Date::Date(std::time_t timer) {
    struct tm *calendar_timer;
    calendar_timer = gmtime(&timer);
    this->mday = calendar_timer->tm_mday;
    this->mmonth = calendar_timer->tm_mon;
    this->myear = calendar_timer->tm_year + 1900;
}

int project::Date::get_month_day() const {
    return this->mday;
}

int project::Date::get_month() const {
    return this->mmonth;
}

int project::Date::get_year() const {
    return this->myear;
}

int project::Date::get_year_day() const {
    return (OveralDayCount[this->get_month()-1] + project::Date::isleap(this->get_year()) + this->get_month_day());
}

constexpr bool project::Date::isleap(int y) {
    if(y%4==0) return true;
    return false;
}

namespace project {
    std::ostream &operator<<(std::ostream &os, const project::Date &date) {
        std::cout << date.mday << "-" << date.mmonth << "-" << date.myear; 
        return os;
    }
}
