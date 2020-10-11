//
// Created by morei on 28/08/2020.
//

#include "FuelBusValve.h"

namespace FuelSystem {
    FuelSystem::FuelBusValve::FuelBusValve(FuelSystem::FuelBus* location1, FuelSystem::FuelBus* location2) {
        this->bus1 = location1;
        this->bus2 = location2;
        this->state = 0;
        this->commandedState = 0;
        this->isPowered = false;
    }

    void FuelSystem::FuelBusValve::setState(int nState) {
        this->commandedState = nState;
        if (this->isPowered) //if the valve is not powered, cant change state
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

    void FuelBusValve::setPower(bool p) {
        this->isPowered = p;
        if (p) // when it gets power again, we revert state to the correct one
            this->state = this->commandedState;
    }

    bool FuelBusValve::getPower() {
        return this->isPowered;
    }

}