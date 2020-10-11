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

        FuelSystem::FuelBusValve** busValvesList{};
        int numBusValves{};

        double* pumpAmounts; //used to speed up calculations
        double* gravFeedAmounts;
        double totalPumpGravFuel;

    public:
        FuelBus(int bNum, FuelSystem::FuelPump** pumps, int nPumps, FuelSystem::FuelTankValve** tankValves, int nTValves, FuelSystem::FuelConsumer** consumers, int nCons);
        ~FuelBus();

        void setBusValves(FuelSystem::FuelBusValve** bValves, int nBValves);
        FuelSystem::FuelBusValve **getBusValves();
        int getNumBusValves();

        int getBusNum();
        void setEfBusNum(int bNum);
        int getEfBusNum();

        double distribute(double amount, float deltaTime);
        double pump(double amount);

        double getMaxAvailGravity(float deltaTime);
        double getMaxAvailPumped(float deltaTime);
    };
}


#endif //UNTITLED_FUELBUS_H
