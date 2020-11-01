//
// Created by morei on 31/08/2020.
//

#ifndef A380_SYSTEMS_EMERGTRANSVALVE_H
#define A380_SYSTEMS_EMERGTRANSVALVE_H

#include "FuelTank.h"

namespace PhysicalFuelSystem {
    class EmergTansValve {
    private:
        int state = 0; // 0=Closed, 1=Opened
        int commandedState;
        bool isPowered;
        double rate;

        PhysicalFuelSystem::FuelTank* upper;
        PhysicalFuelSystem::FuelTank* lower;
    public:
        EmergTansValve(PhysicalFuelSystem::FuelTank *upper, PhysicalFuelSystem::FuelTank *lower);
        void setState(int nState);
        int getState();

        void transfer();

        void setPower(bool p);
        bool getPower();
    };
}


#endif //A380_SYSTEMS_EMERGTRANSVALVE_H
