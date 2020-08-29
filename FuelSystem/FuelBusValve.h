//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELBUSVALVE_H
#define UNTITLED_FUELBUSVALVE_H
#include "FuelBus.h"

namespace FuelSystem {
    class FuelBusValve {
    private:
        FuelSystem::FuelBus* bus1;
        FuelSystem::FuelBus* bus2;
        int state = 0; // 0=Closed, 1=Opened

    public:
        FuelBusValve(FuelBus *location1, FuelBus *location2);
        void setState(int nState);
        int getState() const;
    };
}

#endif //UNTITLED_FUELBUSVALVE_H
