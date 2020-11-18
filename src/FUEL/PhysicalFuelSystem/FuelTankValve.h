//
// Created by MasterWigu on 28/08/2020.
//

#ifndef UNTITLED_FUELTANKVALVE_H
#define UNTITLED_FUELTANKVALVE_H
#include "FuelTank.h"

namespace PhysicalFuelSystem {
    /// @class FuelTankValve represents a valve that connects a bus (aka a pipe) to a tank.
    /// It can be unidirectional (fuel only flows into tank) or bidirectional (fuel can also leave the tank by gravity feeding)
    /// Can be open or closed, and will not work if without power (will stay in the last position)
    /// Gravity feeding can occur if the valve is open even if it is unpowered.
    class FuelTankValve {
    private:
        PhysicalFuelSystem::FuelTank* valveLocation;
        int state = 0; // 0=Closed, 1=Opened
        int commandedState = 0;
        bool isPowered;
        double gravFeedRate = 0;  //if 0, valve cannot gravFeed

    public:
        /// Instantiates a tank fuel valve that cannot gravity feed
        /// @param [in] location - the tank to which the valve is connected to
        explicit FuelTankValve(PhysicalFuelSystem::FuelTank* location);

        /// Instantiates a tank fuel valve that can (or not) gravity feed
        /// @param [in] location - the tank to which the valve is connected to
        /// @param [in] feedRate - the gravity feed rate (if =0, the valve cannot gravity feed)
        FuelTankValve(PhysicalFuelSystem::FuelTank* location, double feedRate);

        /// Commands a new state for the valve (only changes the real state if the valve is powered)
        /// @param [in] nState - the new commanded state for the valve (0=Closed; 1=Open)
        void setState(int nState);

        /// Gets the current state of the valve (open or closed)
        /// @return the state of the valve (0=Closed; 1=Open)
        int getState() const;


        bool canPutInTank();

        /// Puts fuel into the associated tank
        /// @param [in] amount - the amount of fuel we want to put into the tank
        /// @return the amount of fuel in excess that didn't fit in the tank (overflow)
        double putInTank(double amount);

        /// Gets the fuel that the valve can gravity feed (does not remove from tank)
        /// @param [in] deltaTime - the time since last update
        /// @return the amount of fuel it can gravity feed
        double getGravFeedable(float deltaTime);

        /// Gravity feeds some amount of fuel, removing from the tank
        /// @param [in] amount - the amount we want to remove
        void gravityFeed(double amount);


        void setPower(bool p);
        bool getPower();

    };
}



#endif //UNTITLED_FUELTANKVALVE_H
