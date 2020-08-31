//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELSYSTEM_H
#define UNTITLED_FUELSYSTEM_H

#include "FuelBus.h"
#include "EmergTransValve.h"

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
        EmergTansValve** emergValves;

        bool* electricStatus;
        
        bool* enginesFulfilled;

    public:
        FuelSystem();

        void update();

        void printEffectiveNums();

        void testSystem();

        void debugPrint();

        void ACEssChanged(bool powered);
        void AC1Changed(bool powered);
        void AC2Changed(bool powered);
        void AC3Changed(bool powered);
        void AC4Changed(bool powered);
        void DCEssChanged(bool powered);
        void DC1Changed(bool powered);
        void DC2Changed(bool powered);
    };
}




#endif //UNTITLED_FUELSYSTEM_H
