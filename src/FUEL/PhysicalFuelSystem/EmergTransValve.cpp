//
// Created by MasterWigu on 31/08/2020.
//

#include "EmergTransValve.h"

PhysicalFuelSystem::EmergTansValve::EmergTansValve(PhysicalFuelSystem::FuelTank *upper, PhysicalFuelSystem::FuelTank *lower) {
    this->rate = 10000; //I had to guess a value
    this->state = 0;
    this->commandedState = 0;
    this->isPowered = false;
    this->upper = upper;
    this->lower = lower;
}

void PhysicalFuelSystem::EmergTansValve::setState(int nState) {
    this->commandedState = nState;
    if (this->isPowered)  //we only change state if we have power
        this->state = nState;
}

int PhysicalFuelSystem::EmergTansValve::getState() {
    return this->state;
}

void PhysicalFuelSystem::EmergTansValve::transfer() {
    if (state == 1) { //only if valve is open
        double valueToTransfer = this->upper->getFuel();  //max fuel to transfer = upper tank total quantity
        if (valueToTransfer > this->rate) valueToTransfer = this->rate; // limit it by the rate
        double remainder = this->lower->addFuel(valueToTransfer); // limit it to the space in the lower tank
        this->upper->removeFuel(valueToTransfer - remainder); // remove the quantity after all limitations
    }
}

void PhysicalFuelSystem::EmergTansValve::setPower(bool p) {
    this->isPowered = p;
    if (p) //when power is restored, set the last commanded state
        this->state = this->commandedState;
}

bool PhysicalFuelSystem::EmergTansValve::getPower() {
    return this->isPowered;
}
