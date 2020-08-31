//
// Created by morei on 31/08/2020.
//

#include "EmergTransValve.h"

FuelSystem::EmergTansValve::EmergTansValve(FuelSystem::FuelTank *upper, FuelSystem::FuelTank *lower) {
    this->rate = 10000; //I had to guess a value
    this->state = 0;
    this->commandedState = 0;
    this->isPowered = false;
    this->upper = upper;
    this->lower = lower;
}

void FuelSystem::EmergTansValve::setState(int nState) {
    this->commandedState = nState;
    if (this->isPowered)
        this->state = nState;
}

int FuelSystem::EmergTansValve::getState() {
    return this->state;
}

void FuelSystem::EmergTansValve::transfer() {
    if (state == 1) { //only if valve is open
        int valueToTransfer = this->upper->getFuel();
        if (valueToTransfer > this->rate) valueToTransfer = this->rate;
        int remainder = this->lower->addFuel(valueToTransfer);
        this->upper->removeFuel(valueToTransfer - remainder);
    }
}

void FuelSystem::EmergTansValve::setPower(bool p) {
    this->isPowered = p;
    if (p)
        this->state = this->commandedState;
}

bool FuelSystem::EmergTansValve::getPower() {
    return this->isPowered;
}
