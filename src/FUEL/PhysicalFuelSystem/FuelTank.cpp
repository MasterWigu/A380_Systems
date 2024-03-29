#include "FuelTank.h"

namespace PhysicalFuelSystem {

    PhysicalFuelSystem::FuelTank::FuelTank(double capacity) {
        this->capacityKg = capacity;
        this->collectorCapacity = 0;
    }

    PhysicalFuelSystem::FuelTank::FuelTank(double capacity, double collCap) {
        this->capacityKg = capacity;
        this->collectorCapacity = collCap;
    }

    void PhysicalFuelSystem::FuelTank::setFuel(double fuelKg) {
        this->currFuelKg = fuelKg;
    }

    double FuelTank::getFuel() const {
        return this->currFuelKg - this->collectorCapacity; //the fuel in the tank doesn't include collector
    }

    double FuelTank::getCollectorFuel() const {
        if (this->currFuelKg > this->collectorCapacity)
            return this->collectorCapacity; //if the tank has fuel, we assume the collector is full
        return this->currFuelKg;
    }

    double FuelTank::addFuel(double amount) {
        if (this->currFuelKg + amount > this->capacityKg) { //if overfill, set max and return remainder
            double temp = this->currFuelKg + amount - this->capacityKg;
            this->currFuelKg = this->capacityKg;
            return temp; // return the fuel we could not place in tank
        }

        this->currFuelKg+=amount;
        return 0;
    }

    double PhysicalFuelSystem::FuelTank::removeFuel(double amount) {
        if (this->currFuelKg - this->collectorCapacity - amount < 0) {
            double temp = this->currFuelKg - this->collectorCapacity;  //temp is the fuel we could remove until tank empty
            this->currFuelKg = 0;
            return temp; //return the fuel we could get from the tank
        }

        this->currFuelKg-=amount;
        return amount;
    }

    double PhysicalFuelSystem::FuelTank::removeFuelCollector(double amount) {
        if (this->currFuelKg - amount < 0) {
            double temp = this->currFuelKg;  //temp is the fuel we could remove until tank empty
            this->currFuelKg = 0;
            return temp; //return the fuel we could get from the tank
        }

        this->currFuelKg-=amount;
        return amount;
    }


    bool FuelTank::isFull() const {
        if (this->currFuelKg >= this->capacityKg)
            return true;
        return false;
    }

    bool FuelTank::isEmpty() const {
        return this->currFuelKg < this->collectorCapacity;
    }

    bool FuelTank::isCollectorEmpty() const {
        return this->currFuelKg == 0;
    }

    bool FuelTank::hasCollector() {
        return this->collectorCapacity != 0;
    }


}
