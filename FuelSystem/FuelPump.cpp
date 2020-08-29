//
// Created by morei on 28/08/2020.
//

#include "FuelPump.h"


namespace FuelSystem {
    FuelSystem::FuelPump::FuelPump(FuelSystem::FuelTank* location, int rate) {
        this->maxPumpRate = rate;
        this->pumpLocation = location;
    }

    int FuelPump::getPumpable() {
        // IF pump is on, return max that we can pump being it all the fuel in the tank, or the max for the pump
        if (this->state == 1) {
            if (this->pumpLocation->getFuel() >= this->maxPumpRate) {
                return this->maxPumpRate;
            }
            return this->pumpLocation->getFuel();
        }
        return 0;
    }

    void FuelPump::pumpFuel(int amount) {
        // TODO check for addRemFuel not returning 0 (tank did not have enough fuel) (should not happen)
        this->pumpLocation->removeFuel(amount);
    }

    bool FuelPump::canPump() {
        // If pump is on and we have fuel in tank, return true
        if (this->state == 1 && !this->pumpLocation->isEmpty()) {
            return true;
        }
        return false;
    }


}