#include <iostream>
#include "FuelSystem/FuelSystem.h"
#include <chrono>

int main() {
    std::cout << "Hello, World!" << std::endl;
    FuelSystem::FuelSystem f = FuelSystem::FuelSystem();
    //f.printEffectiveNums();
    f.testSystem();
    f.ACEssChanged(true);
    f.AC1Changed(true);
    f.AC2Changed(true);
    f.AC3Changed(true);
    f.AC4Changed(true);
    f.DCEssChanged(true);
    f.DC1Changed(true);
    f.DC2Changed(true);


    for (int i=0;i<10; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();
        f.update();
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "RUN: " << duration << std::endl;
    }
    f.debugPrint();
    //f.printEffectiveNums();

    std::cout << "Hello, World!2" << std::endl;

    //XPLMDataRef testRef = XPLMFindDataRef("sim/cockpit2/controls/flap_ratio");


    return 0;
}
