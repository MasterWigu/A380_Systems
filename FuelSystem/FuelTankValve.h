//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELTANKVALVE_H
#define UNTITLED_FUELTANKVALVE_H
#include "FuelTank.h"

namespace FuelSystem {
    class FuelTankValve {
    private:
        FuelSystem::FuelTank* valveLocation;
        int state = 0; // 0=Closed, 1=Opened
        int gravFeedRate = 0;  //if 0, valve cannot gravFeed

    public:
        explicit FuelTankValve(FuelSystem::FuelTank* location);
        FuelTankValve(FuelSystem::FuelTank* location, int feedRate);

        void setState(int nState);
        int getState() const;

        bool canPutInTank();
        int putInTank(int amount);

        int getGravFeedable();
        void gravityFeed(int amount);
    };
}



#endif //UNTITLED_FUELTANKVALVE_H
