//
// Created by morei on 28/08/2020.
//
#include <cmath>
#include "FuelBus.h"
#include <cstdlib>



PhysicalFuelSystem::FuelBus::FuelBus(int bNum, PhysicalFuelSystem::FuelPump **pumps, int nPumps, PhysicalFuelSystem::FuelTankValve **tankValves, int nTValves, PhysicalFuelSystem::FuelConsumer** consumers, int nCons) {
    this->busNum = bNum;
    this->effectiveBusNum = 0;

    this->pumpsList = (FuelPump**) malloc(nPumps * sizeof(FuelPump*));
    for (int i=0; i<nPumps; i++) {
        this->pumpsList[i] = pumps[i];
    }
    this->numPumps = nPumps;

    this->pumpAmounts = (double*) malloc(nPumps*sizeof(double));
    for (int i = 0; i<nPumps; i++)
        this->pumpAmounts[i] = 0.0;

    this->tankValvesList = (FuelTankValve**) malloc(nTValves * sizeof(FuelTankValve*));
    for (int i=0; i<nTValves; i++) {
        this->tankValvesList[i] = tankValves[i];
    }
    this->numTankValves = nTValves;

    this->gravFeedAmounts = (double*) malloc(nTValves*sizeof(double));
    for (int i = 0; i<nTValves; i++)
        this->gravFeedAmounts[i] = 0.0;

    this->consumersList = (FuelConsumer**) malloc(nCons * sizeof(FuelConsumer*));
    for (int i=0; i<nCons; i++) {
        this->consumersList[i] = consumers[i];
    }
    this->numConsumers = nCons;

    this->totalPumpGravFuel = 0.0;
}

double PhysicalFuelSystem::FuelBus::getMaxAvailPumped(float deltaTime) {
    double availKg = 0.0;

    for (int i = 0; i<this->numPumps; i++) {
        this->pumpAmounts[i] = this->pumpsList[i]->getPumpable(deltaTime);
        availKg += this->pumpAmounts[i];
    }

    for (int i = 0; i< this->numTankValves; i++) {
        this->gravFeedAmounts[i] = 0; // if the fuel is being pumped, the gravity feed is always 0
    }
    this->totalPumpGravFuel = availKg;
    return availKg;

    // TODO case in which the two main buses are connected (fuel made avail twice in mid and inner tanks)

}

double PhysicalFuelSystem::FuelBus::getMaxAvailGravity(float deltaTime) {
    // This function can only be called after getMaxAvailPumped and only if that returned 0!!!!
    double availKg = 0;

    for (int i = 0; i<this->numTankValves; i++) {
        this->gravFeedAmounts[i] = this->tankValvesList[i]->getGravFeedable(deltaTime);
        availKg += this->gravFeedAmounts[i];
    }

    this->totalPumpGravFuel = availKg;
    return availKg;
}

double PhysicalFuelSystem::FuelBus::distribute(double amount, float deltaTime) {
    //consumers have priority always
    for (int i = 0; i<this->numConsumers; i++) {
        if (this->consumersList[i]->canConsume()) {
            amount = this->consumersList[i]->consume(amount, deltaTime);
        }
    }
    if (amount <= 0) {
        return amount;
    }

    int numOpenValves = 0;
    for (int i = 0; i<this->numTankValves; i++) {
        if (this->tankValvesList[i]->getState() == 1)
            numOpenValves++;
    }
    if (numOpenValves == 0) { // if we have no valves open, no need to check if we can spend
        return amount;
    }

    double tempAmount = 0.0; // variable to check if we got to the point we cant spend more fuel
    while (amount > 0 && tempAmount != amount) {
        tempAmount = amount;
        double amountPerValve = amount / numOpenValves; // the amount of fuel to try to send per valve
        for (int i = 0; i<this->numTankValves; i++) {
            if (this->tankValvesList[i]->getState() == 1)
                amount -= this->tankValvesList[i]->putInTank(amountPerValve);
        }
    }
    // returns the amount of fuel it couldn't distribute (if negative, we need to get (more) fuel by grav)
    return amount;
}

double PhysicalFuelSystem::FuelBus::pump(double amount) {
    double percentage = amount / this->totalPumpGravFuel;

    double aux = 0;
    for (int i=0; i<this->numPumps; i++) {
        aux = pumpAmounts[i]*percentage;
        amount -= aux;
        this->pumpsList[i]->pumpFuel(aux);
    }

    if (amount <= 1) // <1 instead of ==0 to compensate rounding errors
        return 0;
    for (int i=0; i<this->numTankValves; i++) {
        aux = gravFeedAmounts[i]*percentage;
        amount -= aux;
        this->tankValvesList[i]->gravityFeed(aux);
    }
    return amount;
}

int PhysicalFuelSystem::FuelBus::getBusNum() {
    return this->busNum;
}

void PhysicalFuelSystem::FuelBus::setEfBusNum(int bNum) {
    this->effectiveBusNum = bNum;
}

int PhysicalFuelSystem::FuelBus::getEfBusNum() {
    return this->effectiveBusNum;
}

void PhysicalFuelSystem::FuelBus::setBusValves(PhysicalFuelSystem::FuelBusValve **bValves, int nBValves) {
    this->busValvesList = (FuelBusValve**) malloc(nBValves * sizeof(FuelBusValve*));
    for (int i=0; i<nBValves; i++) {
        this->busValvesList[i] = bValves[i];
    }
    this->numBusValves = nBValves;
}

PhysicalFuelSystem::FuelBusValve **PhysicalFuelSystem::FuelBus::getBusValves() {
    return this->busValvesList;
}

int PhysicalFuelSystem::FuelBus::getNumBusValves() {
    return this->numBusValves;
}

PhysicalFuelSystem::FuelBus::~FuelBus() {
    free(this->pumpsList);
    free(this->tankValvesList);
    free(this->consumersList);
    free(this->busValvesList);
}
