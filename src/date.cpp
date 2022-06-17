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

project::Date::Weekday project::Date::get_week_day()const {
    return Weekday::Saturday;
    // todo: implement
    // set a reference point and check diff between two dates 
}

// 14
project::Date& project::Date::set_month_day(int day) {
    this->mday = day;
    return *this;
}

// 15
project::Date& project::Date::set_month(int month) {
    this->mmonth = month;
    return *this;
}

// 16
project::Date& project::Date::set_year(int year) {
    this->myear = year;
    return *this;
}

// 17
project::Date& project::Date::set(int day, int mon, int year) {
    this->mday = day;
    this->mmonth = mon;
    this->myear = year;
    return *this;
}   

// 18
project::Date project::Date::operator-(int day) const {
    int tday, tmon, tyear;
    bool isLeapYear = project::Date::isleap(myear);
    tday = mday;
    tmon = mmonth;
    tyear = myear;

    while(day) {
        if(tday>day) {
            tday -= day;
            day -= day;
        }
        else {
            day -= tday;

            tmon--;
            if(tmon == 0) {
                tyear--;
                isLeapYear = project::Date::isleap(tyear);
                tmon = 12;
            }
            tday = DaysInMonths[tmon]; 
            if(isLeapYear == true && tmon == 2) {
                tday++;
            }
            
        }
    }

    return Date(tday, tmon, tyear);
}

// 19
project::Date& project::Date::operator+=(int day) {
    int remainingDaysInCurrMon = DaysInMonths[mmonth] - mday;
    bool isLeapYear = project::Date::isleap(myear);
   
    if(isLeapYear) {
        remainingDaysInCurrMon++;
    }

    while(day) {

        if(remainingDaysInCurrMon>day) {
            mday += day;
            day = 0;
        }
        else {
            day -= remainingDaysInCurrMon;
            mday = 0;
            mmonth++;
            if(mmonth == 13) {
                myear++;
                mmonth = 1;
                isLeapYear = project::Date::isleap(myear);
            }
            remainingDaysInCurrMon = DaysInMonths[mmonth];
            if(isLeapYear == true && mmonth == 2) {
                remainingDaysInCurrMon++;
            }
        }
    }
    return *this;
}

// 20

project::Date& project::Date::operator-=(int day) {
    bool isLeapYear = project::Date::isleap(myear);

    while(day) {
        if(mday>day) {
            mday -= day;
            day -= day;
        }
        else {
            day -= mday;

            mmonth--;
            if(mmonth == 0) {
                myear--;
                isLeapYear = project::Date::isleap(myear);
                mmonth = 12;
            }
            mday = DaysInMonths[mmonth]; 
            if(isLeapYear == true && mmonth == 2) {
                mday++;
            }
            
        }
    }

    return *this;
}

constexpr bool project::Date::isleap(int y) {
    // there are more criterias to check if a year is a leap year but we dont need to take into acount since our min year is 1900!!
    if(y%4==0) return true;
    return false;
}

namespace project {
    std::ostream &operator<<(std::ostream &os, const project::Date &date) {
        std::cout << date.mday << "-" << date.mmonth << "-" << date.myear; 
        return os;
    }
}
