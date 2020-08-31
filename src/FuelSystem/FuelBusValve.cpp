//
// Created by morei on 28/08/2020.
//

#include "FuelBusValve.h"

namespace FuelSystem {
    FuelSystem::FuelBusValve::FuelBusValve(FuelSystem::FuelBus* location1, FuelSystem::FuelBus* location2) {
        this->bus1 = location1;
        this->bus2 = location2;
        this->state = 0;
    }

    void FuelSystem::FuelBusValve::setState(int nState) {
        this->state = nState;
    }

    int FuelBusValve::getState() {
        return this->state;
    }

    FuelBus *FuelBusValve::getLocation1() {
        return this->bus1;
    }

    FuelBus *FuelBusValve::getLocation2() {
        return this->bus2;
    }

}