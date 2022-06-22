#include <iostream>
#include "date.hpp"

int main() {
    
    project::Date mydate1;
    project::Date mydate2(2, 3, 1990);
    project::Date mydate3("02/07/1990");

    time_t epoch = 0;
    project::Date mydate4(epoch);

    std::cout << "Entering main driver func.." << std::endl;
    std::cout << "22-6-2022" << std::endl;

    std::cout << mydate1 << std::endl;
    std::cout << mydate2 << std::endl;
    std::cout << mydate3 << std::endl;
    std::cout << mydate4 << std::endl;


    project::Date mydate5(1, 1, 1990);
    std::cout << mydate5.get_year_day() << std::endl;
    project::Date mydate6(7, 1, 1900);
    std::cout << mydate6.get_year_day() << std::endl;
    project::Date mydate7(26, 12, 1986);
    std::cout << mydate7.get_year_day() << std::endl;
    std::cout << "get_week_day" << std::endl;
    project::Date::Weekday weekday = mydate7.get_week_day();
    std::cout << "(" << mydate7 << ")" << std::endl;
    std::cout << static_cast<int>(weekday) << std::endl;
    std::cout << "get_week_day" << std::endl;
    project::Date::Weekday weekday1 = mydate6.get_week_day();
    std::cout << "(" << mydate6 << ")" << std::endl;
    std::cout << static_cast<int>(weekday1) << std::endl;

    mydate7.set_month_day(30);
    std::cout << mydate7 << std::endl;
    mydate7.set_month(7);
    std::cout << mydate7 << std::endl;
    mydate7.set_year(2000);
    std::cout << mydate7 << std::endl;
    mydate7.set(26,12,1986);
    std::cout << mydate7 << std::endl;

    project::Date mydate8 = mydate7 - 1;
    std::cout << mydate8 << std::endl;

    project::Date mydate9 = mydate7 - 26;
    std::cout << mydate9 << std::endl;

    project::Date mydate10 = mydate7 - 365;
    std::cout << mydate10 << std::endl;

    mydate7.set(1,3,1988);
    project::Date mydate11 = mydate7 - 1;
    std::cout << mydate11 << std::endl;

    std::cout << "Test for operator+= & operator-=" << std::endl;
    mydate10 += 365;
    std::cout << mydate10 << std::endl;
    mydate10 -= 365;
    std::cout << mydate10 << std::endl;

    mydate9 += 26;
    std::cout << mydate9 << std::endl;
    mydate9 -= 26;
    std::cout << mydate9 << std::endl;

    mydate8 += 1;
    std::cout << mydate8 << std::endl;
    mydate8 -= 1;
    std::cout << mydate8 << std::endl;

    mydate11.set(1,2,1988);
    mydate11 += 30;
    std::cout << mydate11 << std::endl;

    mydate11.set(1,2,1989);
    mydate11 += 30;
    std::cout << mydate11 << std::endl;

    ++mydate11;
    std::cout << mydate11 << std::endl;

    mydate10 = mydate11++;
    std::cout << mydate10 << std::endl;
    std::cout << mydate11 << std::endl;

    std::cout << "--" << std::endl;

    mydate10 = --mydate11;
    std::cout << mydate10 << std::endl;
    std::cout << mydate11 << std::endl;

    mydate10 = mydate11--;
    std::cout << mydate10 << std::endl;
    std::cout << mydate11 << std::endl;


    std::cout << "random date" << std::endl;
    project::Date mydate12 = project::Date::random_date();
    project::Date mydate13 = project::Date::random_date();
    project::Date mydate14 = project::Date::random_date();
    std::cout << mydate12 << std::endl;
    std::cout << mydate13 << std::endl;
    std::cout << mydate14 << std::endl;
  
    std::cout << "comparison operators " << std::endl;
    std::cout << (mydate12==mydate13) << std::endl;
    std::cout << (mydate12!=mydate13) << std::endl;
    std::cout << (mydate12>=mydate13) << std::endl;
    std::cout << (mydate12<=mydate13) << std::endl;
    std::cout << (mydate12<mydate13) << std::endl;
    std::cout << "comparison operators " << std::endl;
    std::cout << (mydate13==mydate13) << std::endl;
    std::cout << (mydate13!=mydate13) << std::endl;
    std::cout << (mydate13>=mydate13) << std::endl;
    std::cout << (mydate13<=mydate13) << std::endl;
    std::cout << (mydate12<=mydate13) << std::endl;
    std::cout << (mydate12>=mydate13) << std::endl;

    std::cout << "calculate diff" << std::endl;
    int diff = 0;
    
    mydate10.set(1,2,1989);
    mydate11.set(2,2,1989);
    diff = mydate10 - mydate11;
    std::cout << "(" << mydate10 << ")-(" << mydate11 << ")=" << diff << std::endl;

    mydate10.set(1,2,1989);
    mydate11.set(2,3,1989);
    diff = mydate10 - mydate11;
    std::cout << "(" << mydate10 << ")-(" << mydate11 << ")=" << diff << std::endl;

    mydate10.set(1,2,1989);
    mydate11.set(2,4,1989);
    diff = mydate10 - mydate11;
    std::cout << "(" << mydate10 << ")-(" << mydate11 << ")=" << diff << std::endl;

    mydate10.set(10,2,1962);
    mydate11.set(2,2,1989);
    diff = mydate10 - mydate11;
    std::cout << "(" << mydate10 << ")-(" << mydate11 << ")=" << diff << std::endl;

    mydate10.set(7,1,1900);
    mydate11.set(26,12,1986);
    diff = mydate10 - mydate11;
    std::cout << "(" << mydate10 << ")-(" << mydate11 << ")=" << diff << std::endl;


}