//
// Created by morei on 28/08/2020.
//

#include "FuelPump.h"


namespace PhysicalFuelSystem {
    PhysicalFuelSystem::FuelPump::FuelPump(PhysicalFuelSystem::FuelTank* location, int rate, bool iF) {
        this->maxPumpRate = rate;
        this->pumpLocation = location;
        this->state = 0;
        this->isFailed = false;
        this->hasPower = false;
        this->commandedState = 0;
        this->isFeed = iF;
    }

    double FuelPump::getPumpable(float deltaTime) {
        // IF pump is on, return max that we can pump being it all the fuel in the tank, or the max for the pump
        double maxPumpable = (this->maxPumpRate/ 60.0) * deltaTime;

        if (this->state == 1) {
            if (this->pumpLocation->getFuel() >= maxPumpable) {
                return maxPumpable;
            }
            return this->pumpLocation->getFuel();
        }
        return 0;
    }

    void FuelPump::pumpFuel(double amount) {
        // TODO check for addRemFuel not returning 0 (tank did not have enough fuel) (should not happen) (maybe it can, idk/c)
        if (this->isFeed)
            this->pumpLocation->removeFuelCollector(amount);
        else
            this->pumpLocation->removeFuel(amount);
    }

    bool FuelPump::canPump() {
        // If pump is on and we have fuel in tank, return true
        if (this->state == 1 && !this->pumpLocation->isCollectorEmpty()) { //we can use isCollectorEmpty() because if the tank does not have collector this function is equal to isEmpty()
            return true;
        }
        return false;
    }

    void FuelPump::setState(int s) {
        this->commandedState = s;
        if (this->isFailed || !this->hasPower)
            this->state = 0;
        else
            this->state = s;
    }

    int FuelPump::getState() {
        return this->state;
    }

    void FuelPump::setPower(bool p) {
        if (!p) //if it doesn't have power, state turns to Off
            this->state = 0;
        else //if it has power again, restore commanded state
            this->state = this->commandedState;
        this->hasPower = p;
    }

    bool FuelPump::getPower() {
        return this->hasPower;
    }

    void FuelPump::setFailed(bool f) {
        this->isFailed = f;
        if (f) // if it is failed, state turns to Off
            this->state = 0;
        else //if it is no longer failed, restore commanded state
            this->state = this->commandedState;
    }

    bool FuelPump::getFailed() {
        return this->isFailed;
    }


}