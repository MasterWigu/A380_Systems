//
// Created by morei on 31/08/2020.
//

#ifndef A380_SYSTEMS_EMERGTRANSVALVE_H
#define A380_SYSTEMS_EMERGTRANSVALVE_H

#include "FuelTank.h"

namespace FuelSystem {
    class EmergTansValve {
    private:
        int state = 0; // 0=Closed, 1=Opened
        int commandedState;
        bool isPowered;
        double rate;

        FuelSystem::FuelTank* upper;
        FuelSystem::FuelTank* lower;
    public:
        EmergTansValve(FuelSystem::FuelTank *upper, FuelSystem::FuelTank *lower);
        void setState(int nState);
        int getState();

        void transfer();

        void setPower(bool p);
        bool getPower();
    };
}


#endif //A380_SYSTEMS_EMERGTRANSVALVE_H
