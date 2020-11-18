//
// Created by MasterWigu on 28/08/2020.
//

#ifndef UNTITLED_FUELBUS_H
#define UNTITLED_FUELBUS_H
#include "FuelPump.h"
#include "FuelTankValve.h"
#include "FuelConsumer.h"
#include "FuelBusValve.h"


namespace PhysicalFuelSystem {

    /// FuelBus represents a section of pipe isolated by @class busValve (s) it contains pumps, tank valves and LP valves (consumers)
    class FuelBus {
    private:

        /// busNum is the unique identifier of that bus, and it never changes
        int busNum;

        /// effectiveBusNum is the identifier of the bus when calculating fuel flows, it can change so that two connected buses (by an open busValve) have the same id
        int effectiveBusNum;

        PhysicalFuelSystem::FuelPump** pumpsList;
        int numPumps;

        PhysicalFuelSystem::FuelTankValve** tankValvesList;
        int numTankValves;

        PhysicalFuelSystem::FuelConsumer** consumersList;
        int numConsumers;

        PhysicalFuelSystem::FuelBusValve** busValvesList{};
        int numBusValves{};

        // temp values used to calculate fuel flow in the bus
        double* pumpAmounts;
        double* gravFeedAmounts;
        double totalPumpGravFuel;

    public:

        /// Instantiates a fuel bus with all the components in it (all argument arrays are hard copied!)
        /// @param [in] bNum - bus permanent identifier
        /// @param [in] pumps - pointer to an array of the pumps in the bus
        /// @param [in] nPumps - number of pumps in the bus
        /// @param [in] tankValves - pointer to an array of the tank valves in the bus
        /// @param [in] nTValves - number of tank valves in the bus
        /// @param [in] consumers - pointer to an array of the consumers (LP valves) in the bus
        /// @param [in] nCons - number of consumers (LP valves) in the bus
        FuelBus(int bNum, PhysicalFuelSystem::FuelPump** pumps, int nPumps, PhysicalFuelSystem::FuelTankValve** tankValves, int nTValves, PhysicalFuelSystem::FuelConsumer** consumers, int nCons);
        ~FuelBus();

        /// Informs the bus about the bus valves it is connected to.
        /// @param [in] bValves - pointer to an array of the bus valves the bus is connected to (hard copied!)
        /// @param [in] nBValves - number of bus valves the bus is connected to
        void setBusValves(PhysicalFuelSystem::FuelBusValve** bValves, int nBValves);


        /// Returns the bus valves the bus is connected to
        /// @return pointer to an array of the bus valves
        PhysicalFuelSystem::FuelBusValve **getBusValves();

        /// Returns the number of bus valves the bus is connected to
        /// @return number of bus valves
        int getNumBusValves();

        // these are pretty self explanatory
        int getBusNum();
        void setEfBusNum(int bNum);
        int getEfBusNum();


        /// Distributes the amount of fuel between all the consumers and open tank valves
        /// Gives priority to the consumers
        /// @param [in] amount - the amount of fuel we have to distribute
        /// @param [in] deltaTime - the time (in seconds) that has passed since the last update (needed to convert rates to amounts)
        /// @return the amount of fuel it couldn't distribute (if negative, the fuel was not enough for all *consumers*!)
        double distribute(double amount, float deltaTime);

        /// Commands the pumps to pump an amount of fuel or the valves to get by gravity feeding (subtracts the fuel from the tanks)
        /// @param [in] amount - amount of fuel to pump / gravity feed
        /// @return the amount of fuel it could *not* pump from the asked amount
        double pump(double amount);

        /// Gets the maximum pumped amount of fuel for the time period specified (usually the time since last update)
        /// @param [in] deltaTime - time since last update in seconds
        /// @return the amount of fuel
        double getMaxAvailPumped(float deltaTime);

        /// Gets the maximum gravity fed amount of fuel for the time period specified (usually the time since last update)
        /// This function can only be called after getMaxAvailPumped and only if that returned 0!!!!
        /// @param [in] deltaTime - time since last update in seconds
        /// @return the amount of fuel
        double getMaxAvailGravity(float deltaTime);
    };
}


#endif //UNTITLED_FUELBUS_H
