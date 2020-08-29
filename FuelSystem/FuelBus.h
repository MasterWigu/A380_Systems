//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELBUS_H
#define UNTITLED_FUELBUS_H

#include "FuelTank.h"
#include "FuelPump.h"
#include "FuelTankValve.h"
#include "FuelConsumer.h"

namespace FuelSystem {
    class FuelBus {
    private:
        FuelSystem::FuelPump** pumpsList;
        int numPumps;
        FuelSystem::FuelTankValve** tankValvesList;
        int numTankValves;

        FuelSystem::FuelConsumer** consumersList;
        int numConsumers;

        int* pumpAmounts; //used to speed up calculations
        int* gravFeedAmounts;
        int totalPumpGravFuel;

    public:
        FuelBus(FuelSystem::FuelPump** pumps, int nPumps, FuelSystem::FuelTankValve** tankValves, int nTValves, FuelSystem::FuelConsumer** consumers, int nCons);

        int getMaxAvail();
        int distribute(int amount);
        int pump(int amount);

    };
}


#endif //UNTITLED_FUELBUS_H
