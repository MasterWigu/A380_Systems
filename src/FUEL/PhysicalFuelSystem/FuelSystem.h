//
// Created by MasterWigu on 28/08/2020.
//

#ifndef UNTITLED_FUELSYSTEM_H
#define UNTITLED_FUELSYSTEM_H

#include "FuelBus.h"
#include "EmergTransValve.h"

namespace PhysicalFuelSystem {

    /// @class FuelSystem is the main class of the physical fuel system.
    /// It is responsible for the initialization and creation of the whole system and to update the real quantities
    /// of fuel and the real state of the valves and pumps.
    /// It also simulates the flows of fuel according to the configuration of valves and pumps commanded by the plane computers
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

        // variable that stores the last status of the elec buses
        bool* electricStatus;

        // variable that stores if all engines were fully supplied with fuel in the last update
        bool* enginesFulfilled;

        // variables used to keep track of the time that passes between updates to correctly calculate amounts from rates
        float lastSimTime;
        float simTime;

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the AC ESS bus changes its state
        /// @param [in] powered - the new state of the AC ESS bus
        void ACEssChanged(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the AC1 bus changes its state
        /// @param [in] powered - the new state of the AC1 bus
        void AC1Changed(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the AC2 bus changes its state
        /// @param [in] powered - the new state of the AC2 bus
        void AC2Changed(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the AC3 bus changes its state
        /// @param [in] powered - the new state of the AC3 bus
        void AC3Changed(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the AC4 bus changes its state
        /// @param [in] powered - the new state of the AC4 bus
        void AC4Changed(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the DC ESS bus changes its state
        /// @param [in] powered - the new state of the DC ESS bus
        void DCEssChanged(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the DC1 bus changes its state
        /// @param [in] powered - the new state of the DC1 bus
        void DC1Changed(bool powered);

        /// Function that changes the power state of the valves and pumps according to the elec status.
        /// Used if the DC2 bus changes its state
        /// @param [in] powered - the new state of the DC2 bus
        void DC2Changed(bool powered);

    public:
        /// Instantiates the whole fuel system as per the real system. The system starts empty and with all pumps off and valves closed.
        FuelSystem();

        /// Triggers an update of the whole system (status of pumps, valves, calculation of tank levels, flows of fuel, etc)
        /// @param [in] simulatorTime - the current simulator time in seconds (used to calculate the elapsed time since last update)
        void update(float simulatorTime);

        // only used for debug
        void printEffectiveNums();
        void testSystem();
        void debugPrint();


        /// Function to read the quantity in some tank or collector cell
        /// @param [in] i - the id of the tank (0-10: Tanks, 11-14: Collector cells)
        /// @return the quantity in the specified tank
        double readQuantity(int i);

        /// Function to read the real status of some valve
        /// @param [in] i - the id of the valve according to the id table
        /// @return the real status of the valve (0=Closed; 1=Open)
        int readValveState(int id);

        /// Commands a new state for some valve
        /// @param [in] i - the id of the valve according to the id table
        /// @param [in] state - the new state for the valve (0=Closed; 1=Open)
        void setValveState(int id, int state);

        /// Function to read the real status of some pump
        /// @param [in] i - the id of the pump according to the id table
        /// @return the real status of the pump (0=Off; 1=On)
        int readPumpState(int id);

        /// Commands a new state for some pump
        /// @param [in] i - the id of the pump according to the id table
        /// @param [in] state - the new state for the valve (0=Closed; 1=Open)
        void setPumpState(int id, int state);

    };
}




#endif //UNTITLED_FUELSYSTEM_H
