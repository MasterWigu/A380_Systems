//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELTANKVALVE_H
#define UNTITLED_FUELTANKVALVE_H
#include "FuelTank.h"

namespace PhysicalFuelSystem {
    class FuelTankValve {
    private:
        PhysicalFuelSystem::FuelTank* valveLocation;
        int state = 0; // 0=Closed, 1=Opened
        int commandedState = 0;
        bool isPowered;
        double gravFeedRate = 0;  //if 0, valve cannot gravFeed

    public:
        explicit FuelTankValve(PhysicalFuelSystem::FuelTank* location);
        FuelTankValve(PhysicalFuelSystem::FuelTank* location, double feedRate);

        void setState(int nState);
        int getState() const;

        bool canPutInTank();
        double putInTank(double amount);

        double getGravFeedable(float deltaTime);
        void gravityFeed(double amount);

        void setPower(bool p);
        bool getPower();

    };
}



#endif //UNTITLED_FUELTANKVALVE_H
