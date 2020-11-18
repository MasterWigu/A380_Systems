//
// Created by MasterWigu on 31/08/2020.
//

#ifndef A380_SYSTEMS_EMERGTRANSVALVE_H
#define A380_SYSTEMS_EMERGTRANSVALVE_H

#include "FuelTank.h"

namespace PhysicalFuelSystem {

    /// @class EmergTransValve Represents an Emergency Transfer Valve
    /// Can be open or closed, and will not work if without power (will stay in the last position)
    /// Connects two tanks directly and transfers from the upper to the lower tank with the provided rate.
    class EmergTansValve {
    private:
        /// Real state of the valve
        int state = 0; // 0=Closed, 1=Opened

        int commandedState;
        bool isPowered;
        double rate;


        PhysicalFuelSystem::FuelTank* upper;
        PhysicalFuelSystem::FuelTank* lower;
    public:

        /// Instantiates an Emergency Transfer Valve with rate = 10000 kg/minute
        /// @param [in] upper pointer to the upper fuel tank (from where the fuel comes)
        /// @param [in] lower pointer to the lower fuel tank (to where the fuel goes)
        EmergTansValve(PhysicalFuelSystem::FuelTank *upper, PhysicalFuelSystem::FuelTank *lower);

        /// Commands a new state to the valve
        /// @param [in] nState integer that represents the new commanded state (0=Closed; 1=Open)
        void setState(int nState);

        /// Gets the current state of the valve
        /// @return int current state (0=Closed; 1=Open)
        int getState();

        /// Transfers fuel from the upper tank to the lower according to the rate and the elapsed time since the last update cycle
        //TODO add elapsed time
        void transfer();

        /// Sets the power to the valve making it work or not
        /// @param [in] p boolean representing the power (true=present; false=absent)
        void setPower(bool p);


        bool getPower();
    };
}


#endif //A380_SYSTEMS_EMERGTRANSVALVE_H
