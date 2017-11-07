#include "ConsoleDisplay.h"

#include <cstdlib>
#include <iostream>

void ConsoleDisplay::show(int number)
{
    // FIXME: calling system is not good
    system("clear");
    for (int i = 0; i < number; ++i) {
        std::cout << i + 1;
    }
    std::cout << std::endl;
}
