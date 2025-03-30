#include <iostream>
#include "Thermostat.h"

int main() {
    Thermostat test(25.4, false);
    std::cout << "Current Temp: " << test.getTemperature() << std::endl;
    return 0;
}   
