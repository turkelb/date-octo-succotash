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


}