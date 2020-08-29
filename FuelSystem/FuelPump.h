//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELPUMP_H
#define UNTITLED_FUELPUMP_H
#include "FuelTank.h"


namespace FuelSystem{
    class FuelPump {
    private:
        int maxPumpRate = 0; //In kg/h
        int state = 0; // 0-Off, 1-On

        FuelSystem::FuelTank* pumpLocation;

    public:
        FuelPump(FuelSystem::FuelTank* location, int rate);
        int getPumpable();
        bool canPump();
        void pumpFuel(int amount);
    };
}



#endif //UNTITLED_FUELPUMP_H
