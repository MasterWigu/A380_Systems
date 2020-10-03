//
// Created by morei on 28/08/2020.
//

#include "FuelTankValve.h"

namespace FuelSystem {

    FuelSystem::FuelTankValve::FuelTankValve(FuelSystem::FuelTank *location) {
        this->valveLocation = location;
        this->state = 0;
        this->isPowered = false;
        this->commandedState = 0;
    }

    FuelTankValve::FuelTankValve(FuelSystem::FuelTank *location, double feedRate) {
        this->valveLocation = location;
        this->state = 0;
        this->commandedState = 0;
        this->isPowered = false;
        this->gravFeedRate = feedRate;
    }

    void FuelSystem::FuelTankValve::setState(int nState) {
        this->commandedState = nState;
        if (this->isPowered) //if the valve is not powered, cant change state
            this->state = nState;
    }

    int FuelTankValve::getState() const {
        return this->state;
    }

    double FuelTankValve::getGravFeedable(float deltaTime) {
        double maxFeedable = (this->gravFeedRate / 60.0) * deltaTime;

        if (this->state == 1 && maxFeedable != 0) {
            if (this->valveLocation->getFuel() > maxFeedable) {
                return maxFeedable;
            }
            return this->valveLocation->getFuel();
        }
        return 0;
    }

    bool FuelTankValve::canPutInTank() {
        // 0=Closed, 1=Opened
        if (this->state == 1 || this->state == -2) { //if the state is right
            if (!this->valveLocation->isFull())
                return true;
        }
        return false;
    }

    double FuelTankValve::putInTank(double amount) {
        return this->valveLocation->addFuel(amount);
    }

    void FuelTankValve::gravityFeed(double amount) {
        this->valveLocation->removeFuel(amount);
    }

    void FuelTankValve::setPower(bool p) {
        this->isPowered = p;
        if (p) // when it gets power again, we revert state to the correct one
            this->state = this->commandedState;
    }

    bool FuelTankValve::getPower() {
        return this->isPowered;
    }
}