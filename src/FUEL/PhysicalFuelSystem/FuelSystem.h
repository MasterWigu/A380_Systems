//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELSYSTEM_H
#define UNTITLED_FUELSYSTEM_H

#include "FuelBus.h"
#include "EmergTransValve.h"

namespace PhysicalFuelSystem {
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

        float lastSimTime;
        float simTime;

    public:
        FuelSystem();

        void update(float simulatorTime);

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

        double readQuantity(int i);
        int readValveState(int id);
        void setValveState(int id, int state);
        int readPumpState(int id);
        void setPumpState(int id, int state);



    };
}




#endif //UNTITLED_FUELSYSTEM_H
