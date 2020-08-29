//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELSYSTEM_H
#define UNTITLED_FUELSYSTEM_H

#include "FuelBus.h"
#include "FuelBusValve.h"

namespace FuelSystem {
    class FuelSystem {
    private:

        // arrays of components
        FuelTank* tanks;
        FuelPump* pumps;
        FuelTankValve* tankValves;
        FuelBusValve* busValves;

    public:
        FuelSystem();
    };
}




#endif //UNTITLED_FUELSYSTEM_H
