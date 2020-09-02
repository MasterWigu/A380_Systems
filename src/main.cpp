#include <iostream>
#include "FuelSystem/FuelSystem.h"
#include "PlaneFuelSystem/FuelDistributor.h"
#include <chrono>
#include <fstream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    /*FuelSystem::FuelSystem f = FuelSystem::FuelSystem();
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
    //f.printEffectiveNums();*/

    auto* f = new PlaneFuelSystem::DistributionTables();

    std::ofstream file;
    file.open("outTrim.txt");

    int* fuels = (int*) malloc(15*sizeof(int));
    for (int i = 100; i <= 288900; i += 100) {
        for (int j=29; j <=43; j++) {
            fuels[j-29] = f->calculateTrimFuel(280000, i, j);
        }
        file << i << "; " << fuels[0] << "; " << fuels[1] << "; " << fuels[2] << "; " << fuels[3] << "; " << fuels[4] << "; " << fuels[5] << "; " << fuels[6] << "; " << fuels[7] << "; " << fuels[8] << "; " << fuels[9] << "; " << fuels[10] << "; " << fuels[11] << "; " << fuels[12] << "; " << fuels[13] << "; " << fuels[14] << "; " << fuels[15] << "; " << std::endl;
    }
    file.close();



    std::cout << "Hello, World!2" << std::endl;

    //XPLMDataRef testRef = XPLMFindDataRef("sim/cockpit2/controls/flap_ratio");


    return 0;
}
