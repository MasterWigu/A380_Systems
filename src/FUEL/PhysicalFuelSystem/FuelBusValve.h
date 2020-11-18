//
// Created by MasterWigu on 28/08/2020.
//

#ifndef UNTITLED_FUELBUSVALVE_H
#define UNTITLED_FUELBUSVALVE_H


namespace PhysicalFuelSystem {
    class FuelBus;

    /// @class FuelBusValve Represents a valve that connects two fuel buses together
    /// Can be open or closed, and will not work if without power (will stay in the last position)
    /// Connects two buses directly and allows transfer between them in any direction
    /// NOTE: This valve does not really carry fuel, it is just used by the code to determine if two buses are connected together or not. If the valve is closed, it appears as if the buses were not connected
    class FuelBusValve {
    private:

        /// The real state of the valve (0=Closed, 1=Opened)
        int state = 0; // 0=Closed, 1=Opened

        /// The commanded state of the valve (0=Closed, 1=Opened)
        int commandedState;

        /// State variable that represents if the valve has power or not
        bool isPowered;

        PhysicalFuelSystem::FuelBus* bus1;
        PhysicalFuelSystem::FuelBus* bus2;
    public:

        /// Instantiates an Fuel Bus Valve
        /// @param [in] location1 - one of the connected buses
        /// @param [in] location2 - the other connected bus
        FuelBusValve(PhysicalFuelSystem::FuelBus *location1, PhysicalFuelSystem::FuelBus *location2);


        void setState(int nState);
        int getState();

        FuelBus* getLocation1();
        FuelBus* getLocation2();

        void setPower(bool p);
        bool getPower();
    };
}

#endif //UNTITLED_FUELBUSVALVE_H
