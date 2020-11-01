#include <iostream>
#include "FUEL/SystemControl.h"
#include <chrono>
#include <fstream>
#include <cstring>

int main() {

    char* aa = (char*) malloc(100*sizeof(char));
    strcpy(aa, u8"☐ -ALL TKs");
    strcat(aa, u8"\n☑ -IDK HELP ME ........... OFF\n\n");
    std::cout << aa << std::endl << std::endl;

    std::ofstream file;
    file.open("testu8.txt");
    file << aa;
    file.close();

    /*
    std::cout << "Hello, World!" << std::endl;
    PlaneFuelSystem::SystemControl* s = new PlaneFuelSystem::SystemControl();

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i=0;i<10000; i++) {

        s->update(100, 430000, 41.5, 10);

    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "RUN: " << duration << std::endl;
    //f.printEffectiveNums();*/
    /*
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

    */

    std::cout << "Hello, World!2" << std::endl;

    //XPLMDataRef testRef = XPLMFindDataRef("sim/cockpit2/controls/flap_ratio");


    return 0;
}
