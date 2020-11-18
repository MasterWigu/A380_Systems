//
// Created by MasterWigu on 28/08/2020.
//

#ifndef UNTITLED_FUELPUMP_H
#define UNTITLED_FUELPUMP_H
#include "FuelTank.h"


namespace PhysicalFuelSystem{

    /// @class FuelPump represents a fuel pump that is located in some tank
    /// Can be commanded on or off, and will not work if without power
    /// Can also be set as failed, in which case it will not work
    /// If it is a feed pump, it will get fuel from the collector cell of the tank instead of the tank
    /// It has a maximum pump rate, but can pump less than that
    class FuelPump {
    private:
        double maxPumpRate = 0; //In kg/min
        int state = 0; // 0-Off, 1-On
        int commandedState;
        bool hasPower;
        bool isFailed;
        bool isFeed;

        PhysicalFuelSystem::FuelTank* pumpLocation;

    public:
        /// Instantiates a Fuel Pump
        /// @param [in] location - the tank in which the pump is located
        /// @param [in] rate - the maximum rate the pump is able to pump (in kg/min)
        /// @param [in] iF - if this pump is a feed pump (instead of a transfer pump)
        FuelPump(PhysicalFuelSystem::FuelTank* location, int rate, bool iF);

        /// Gets the maximum amount of fuel the pump can pump in the specified time period, limited by the max rate of the fuel in the tank
        /// @param [in] deltaTime - the time since the last update
        /// @return the amount of fuel
        double getPumpable(float deltaTime);

        bool canPump();

        /// Tells the pump to pump some amount of fuel from the tank (it does not check rate!)
        /// @param [in] amount - the amount of fuel to pump
        void pumpFuel(double amount);


        void setState(int s);
        int getState();

        void setPower(bool p);
        bool getPower();

        void setFailed(bool f);
        bool getFailed();

    };
}



#endif //UNTITLED_FUELPUMP_H
