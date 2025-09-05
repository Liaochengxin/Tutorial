#include <iostream>
#include "include/operator.h"

int main(){
    using namespace ops;

    std::cout << "3.2 + 3 = " << ops::add(3.2, 3) << std::endl; // mixed type: double + int
    std::cout << "3 + 4 = " << ops::add(3, 4) << std::endl;     // int + int
    std::cout << "2.5 + 2.5 = " << ops::add(2.5, 2.5) << std::endl; // double + double

    return 0;
}
