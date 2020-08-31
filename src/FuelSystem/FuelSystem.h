//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELSYSTEM_H
#define UNTITLED_FUELSYSTEM_H

#include "FuelBus.h"

namespace FuelSystem {
    class FuelSystem {
    private:

        // arrays of components
        FuelTank** tanks;
        FuelPump** pumps;
        FuelTankValve** tankValves;
        FuelBusValve** busValves;
        FuelBus** fuelBuses;
        FuelConsumer** consumers;
        
        bool* enginesFulfilled;

    public:
        FuelSystem();

        void update();

        void printEffectiveNums();

        void testSystem();

        void debugPrint();
    };
}




#endif //UNTITLED_FUELSYSTEM_H
