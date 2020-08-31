//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELBUS_H
#define UNTITLED_FUELBUS_H
#include "FuelPump.h"
#include "FuelTankValve.h"
#include "FuelConsumer.h"
#include "FuelBusValve.h"


namespace FuelSystem {
    class FuelBus {
    private:
        int busNum;
        int efectiveBusNum;

        FuelSystem::FuelPump** pumpsList;
        int numPumps;
        FuelSystem::FuelTankValve** tankValvesList;
        int numTankValves;

        FuelSystem::FuelConsumer** consumersList;
        int numConsumers;

        FuelSystem::FuelBusValve** busValvesList;
        int numBusValves;

        int* pumpAmounts; //used to speed up calculations
        int* gravFeedAmounts;
        int totalPumpGravFuel;

    public:
        FuelBus(int bNum, FuelSystem::FuelPump** pumps, int nPumps, FuelSystem::FuelTankValve** tankValves, int nTValves, FuelSystem::FuelConsumer** consumers, int nCons);
        ~FuelBus();

        void setBusValves(FuelSystem::FuelBusValve** bValves, int nBValves);
        FuelSystem::FuelBusValve **getBusValves();
        int getNumBusValves();

        int getBusNum();
        void setEfBusNum(int bNum);
        int getEfBusNum();

        int distribute(int amount);
        int pump(int amount);

        int getMaxAvailGravity();
        int getMaxAvailPumped();
    };
}


#endif //UNTITLED_FUELBUS_H
