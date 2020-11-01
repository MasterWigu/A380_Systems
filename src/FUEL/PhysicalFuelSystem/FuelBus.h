//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELBUS_H
#define UNTITLED_FUELBUS_H
#include "FuelPump.h"
#include "FuelTankValve.h"
#include "FuelConsumer.h"
#include "FuelBusValve.h"


namespace PhysicalFuelSystem {
    class FuelBus {
    private:
        int busNum;
        int efectiveBusNum;

        PhysicalFuelSystem::FuelPump** pumpsList;
        int numPumps;

        PhysicalFuelSystem::FuelTankValve** tankValvesList;
        int numTankValves;

        PhysicalFuelSystem::FuelConsumer** consumersList;
        int numConsumers;

        PhysicalFuelSystem::FuelBusValve** busValvesList{};
        int numBusValves{};

        double* pumpAmounts; //used to speed up calculations
        double* gravFeedAmounts;
        double totalPumpGravFuel;

    public:
        FuelBus(int bNum, PhysicalFuelSystem::FuelPump** pumps, int nPumps, PhysicalFuelSystem::FuelTankValve** tankValves, int nTValves, PhysicalFuelSystem::FuelConsumer** consumers, int nCons);
        ~FuelBus();

        void setBusValves(PhysicalFuelSystem::FuelBusValve** bValves, int nBValves);
        PhysicalFuelSystem::FuelBusValve **getBusValves();
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
