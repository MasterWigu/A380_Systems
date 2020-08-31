//
// Created by morei on 28/08/2020.
//

#include "FuelTank.h"

namespace FuelSystem {

    FuelSystem::FuelTank::FuelTank(int capacity) {
        this->capacityKg = capacity;
    }

    void FuelSystem::FuelTank::setFuel(int fuelKg) {
        this->currFuelKg = fuelKg;
    }

    int FuelTank::getFuel() const {
        return this->currFuelKg;
    }

    int FuelTank::addFuel(int amount) {
        if (this->currFuelKg + amount > this->capacityKg) { //if overfill, set max and return remainder
            int temp = this->currFuelKg + amount - this->capacityKg;
            this->currFuelKg = this->capacityKg;
            return temp; // return the fuel we could not place in tank
        }

        this->currFuelKg+=amount;
        return 0;
    }

    int FuelSystem::FuelTank::removeFuel(int amount) {
        if (this->currFuelKg - amount < 0) {
            int temp = this->currFuelKg;  //temp is the fuel we could remove until tank empty
            this->currFuelKg = 0;
            return temp; //return the fuel we could get from the tank
        }

        this->currFuelKg-=amount;
        return 0;
    }


    bool FuelTank::isFull() const {
        if (this->currFuelKg >= this->capacityKg)
            return true;
        return false;
    }

    bool FuelTank::isEmpty() const {
        return this->currFuelKg == 0;
    }


}
