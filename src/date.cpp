#include <iostream>
#include <sstream>
#include <random>
#include <string>
#include "date.hpp"

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
    // set a reference point and check diff between two dates 
    // 7/1/1900 is our reference date..
    int diff = *this - Date(7,1,1900);
    return static_cast<Weekday>(diff % 7);
}

project::Date& project::Date::set_month_day(int day) {
    this->mday = day;
    return *this;
}

project::Date& project::Date::set_month(int month) {
    this->mmonth = month;
    return *this;
}

project::Date& project::Date::set_year(int year) {
    this->myear = year;
    return *this;
}

project::Date& project::Date::set(int day, int mon, int year) {
    this->mday = day;
    this->mmonth = mon;
    this->myear = year;
    return *this;
}   

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

project::Date& project::Date::operator++() {
    *this += 1;
    return *this;
}

project::Date project::Date::operator++(int) {
    project::Date temp = *this;
    ++*this;
    return temp;
}

project::Date& project::Date::operator--() {
    *this -= 1;
    return *this;
}

project::Date project::Date::operator--(int) {
    project::Date temp = *this;
    --*this;
    return temp;
}

project::Date project::Date::random_date() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr_year(project::Date::random_min_year, project::Date::random_max_year);
    int year = distr_year(generator);

    std::uniform_int_distribution<int> distr_mon(1, 12);
    int month = distr_mon(generator);

    int dayMax = (month==2 && project::Date::isleap(year)) ? (project::Date::DaysInMonths[month]+1) : project::Date::DaysInMonths[month];
    std::uniform_int_distribution<int> distr_day(1, dayMax);
    int day = distr_day(generator);


    return project::Date(day, month, year);
}

constexpr bool project::Date::isleap(int y) {
    // there are more criterias to check if a year is a leap year but we dont need to take into acount since our min year is 1900!!
    if(y%4==0) return true;
    return false;
}

namespace project {
    bool operator<(const Date& leftDate, const Date& rightDate) {
        if(leftDate.get_year()<rightDate.get_year()) {
            return true;
        }
        else if(leftDate.get_year()>rightDate.get_year()) {
            return false;
        }
        else {
            if(leftDate.get_month()<rightDate.get_month()) {
                return true;
            } 
            else if(leftDate.get_month()>rightDate.get_month()) {
                return false;
            }
            else {
                if(leftDate.get_month_day()<rightDate.get_month_day())  {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }

    bool operator==(const Date& leftDate, const Date& rightDate) {
        if(leftDate.get_year()!=rightDate.get_year()) {
            return false;
        }
        else {
            if(leftDate.get_month()!=rightDate.get_month()) {
                return false;
            }
            else {
                if(leftDate.get_month_day()!=rightDate.get_month_day()) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }
	
    bool operator<=(const Date& leftDate, const Date& rightDate) {
        if(leftDate<rightDate || leftDate==rightDate) {
            return true;
        }
        return false;
    }

    bool operator>(const Date& leftDate, const Date& rightDate) {
        if(!(leftDate<=rightDate)) {
            return true;
        }

        return false;
    }

    bool operator>=(const Date& leftDate, const Date& rightDate) { 
        if(leftDate>rightDate || leftDate==rightDate) {
            return true;
        }
        return false;
    }

    bool operator!=(const Date& leftDate, const Date& rightDate) { 
        if(!(leftDate==rightDate)) {
            return true;
        }
        return false;
    }

    int operator-(const Date &d1, const Date &d2) {
        if(d1==d2) return 0;
        
        std::cout << "Operator-" << std::endl;

        Date newerDate;
        Date olderDate;
        if(d1>d2) {
            newerDate = d1;
            olderDate = d2;
        } 
        else {
            newerDate = d2;
            olderDate = d1;       
        }

        int dayToAdd = 0;
        dayToAdd = newerDate.get_year_day();
        newerDate -= dayToAdd;

        int dayToRemove = olderDate.get_year_day();
        olderDate -= dayToRemove;

        int day;
        day = dayToAdd - dayToRemove;

        while(newerDate.get_year()!=olderDate.get_year()) {
            int temp = project::Date::isleap(olderDate.get_year()) ? (366) : (365);
            day += temp;
            olderDate += temp;
        }

        return day;
    }

    project::Date operator+(const project::Date &date, int n) {
        project::Date temp = date;  
        temp += n;
        return temp;
    }

    project::Date operator+(int n, const Date &date) {
        project::Date temp = date;  
        temp += n;
        return temp;
    }

    project::Date::Weekday& operator++(project::Date::Weekday &r) {
        r = static_cast<project::Date::Weekday>((static_cast<int>(r)+1) % 7);
        return r;
    }

    project::Date::Weekday operator++(project::Date::Weekday &r, int) {
        project::Date::Weekday temp = r;
        r = static_cast<project::Date::Weekday>((static_cast<int>(r)+1) % 7);
        return temp;
    }

    project::Date::Weekday& operator--(project::Date::Weekday &r) {
        int tempInt = static_cast<int>(r);
        if(tempInt==0) {
            tempInt = 7;
        }

        r = static_cast<project::Date::Weekday>((tempInt-1) % 7);
        return r;
    }

    project::Date::Weekday operator--(project::Date::Weekday &r, int) {
        project::Date::Weekday temp = r;
        int tempInt = static_cast<int>(r);
        if(tempInt==0) {
            tempInt = 7;
        }
        r = static_cast<project::Date::Weekday>((tempInt-1) % 7);
        return temp;
    }

    std::ostream &operator<<(std::ostream &os, const project::Date &date) {
        std::cout << date.mday << "-" << date.mmonth << "-" << date.myear; 
        return os;
    }

    std::istream &operator>>(std::istream &is, Date &date) {
        std::string input;
        std::getline(std::cin, input);
        std::istringstream line(input);
        std::getline(line, input, '/');
        date.mday = stoi(input);
        std::getline(line, input, '/');
        date.mmonth = stoi(input);
        std::getline(line, input, '/');
        date.myear = stoi(input);
        return is;
    }
}
