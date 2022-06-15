#include <iostream>
#include "date.hpp"

int main() {
    
    project::Date mydate1;
    project::Date mydate2(2, 3, 1990);
    project::Date mydate3("02/07/1990");

    time_t epoch = 0;
    project::Date mydate4(epoch);

    std::cout << "Entering main driver func.." << std::endl;

    std::cout << mydate1 << std::endl;
    std::cout << mydate2 << std::endl;
    std::cout << mydate3 << std::endl;
    std::cout << mydate4 << std::endl;


    project::Date mydate5(1, 1, 1990);
    std::cout << mydate5.get_year_day() << std::endl;
    project::Date mydate6(1, 2, 1990);
    std::cout << mydate6.get_year_day() << std::endl;
    project::Date mydate7(3, 3, 1990);
    std::cout << mydate7.get_year_day() << std::endl;


}