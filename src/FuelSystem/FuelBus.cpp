//
// Created by morei on 28/08/2020.
//
#include <cmath>
#include "FuelBus.h"
#include <cstdlib>



FuelSystem::FuelBus::FuelBus(int bNum, FuelSystem::FuelPump **pumps, int nPumps, FuelSystem::FuelTankValve **tankValves, int nTValves, FuelSystem::FuelConsumer** consumers, int nCons) {
    this->busNum = bNum;
    this->efectiveBusNum = 0;

    this->pumpsList = (FuelPump**) malloc(nPumps * sizeof(FuelPump*));
    for (int i=0; i<nPumps; i++) {
        this->pumpsList[i] = pumps[i];
    }
    this->numPumps = nPumps;

    this->pumpAmounts = (int*) malloc(nPumps*sizeof(int));
    for (int i = 0; i<nPumps; i++)
        this->pumpAmounts[i] = 0;

    this->tankValvesList = (FuelTankValve**) malloc(nTValves * sizeof(FuelTankValve*));
    for (int i=0; i<nTValves; i++) {
        this->tankValvesList[i] = tankValves[i];
    }
    this->numTankValves = nTValves;

    this->gravFeedAmounts = (int*) malloc(nTValves*sizeof(int));;
    for (int i = 0; i<nTValves; i++)
        this->gravFeedAmounts[i] = 0;

    this->consumersList = (FuelConsumer**) malloc(nCons * sizeof(FuelConsumer*));
    for (int i=0; i<nCons; i++) {
        this->consumersList[i] = consumers[i];
    }
    this->numConsumers = nCons;

    this->totalPumpGravFuel = 0;
}

int FuelSystem::FuelBus::getMaxAvailPumped() {
    int availKg = 0;

    for (int i = 0; i<this->numPumps; i++) {
        this->pumpAmounts[i] = this->pumpsList[i]->getPumpable();
        availKg += this->pumpAmounts[i];
    }

    for (int i = 0; i< this->numTankValves; i++) {
        this->gravFeedAmounts[i] = 0; // if the fuel is being pumped, the gravity feed is always 0
    }
    this->totalPumpGravFuel = availKg;
    return availKg;

    // TODO case in which the two main buses are connected (fuel made avail twice in mid and inner tanks)

}

int FuelSystem::FuelBus::getMaxAvailGravity() {
    // This function can only be called after getMaxAvailPumped and only if that returned 0!!!!
    int availKg = 0;

    for (int i = 0; i<this->numTankValves; i++) {
        this->gravFeedAmounts[i] = this->tankValvesList[i]->getGravFeedable();
        availKg += this->gravFeedAmounts[i];
    }

    this->totalPumpGravFuel = availKg;
    return availKg;
}

int FuelSystem::FuelBus::distribute(int amount) {
    //consumers have priority always
    for (int i = 0; i<this->numConsumers; i++) {
        if (this->consumersList[i]->canConsume()) {
            amount = this->consumersList[i]->consume(amount);
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

    int tempAmount = 0; // variable to check if we got to the point we cant spend more fuel
    while (amount > 0 && tempAmount != amount) {
        tempAmount = amount;
        int amountPerValve = amount / numOpenValves; // the amount of fuel to try to send per valve
        for (int i = 0; i<this->numTankValves; i++) {
            if (this->tankValvesList[i]->getState() == 1)
                amount -= this->tankValvesList[i]->putInTank(amountPerValve);
        }
    }
    // returns the amount of fuel it couldn't distribute (if negative, we need to get (more) fuel by grav)
    return amount;
}

int FuelSystem::FuelBus::pump(int amount) {
    double percentage = (double)amount / (double)this->totalPumpGravFuel;


    int aux = 0;
    for (int i=0; i<this->numPumps; i++) {
        aux = (int)std::round(pumpAmounts[i]*percentage);
        amount -= aux;
        this->pumpsList[i]->pumpFuel(aux);
    }

    if (amount <= 1) // <1 instead of ==0 to compensate rounding errors
        return 0;
    for (int i=0; i<this->numTankValves; i++) {
        aux = (int)std::round(gravFeedAmounts[i]*percentage);
        amount -= aux;
        this->tankValvesList[i]->gravityFeed(aux);
    }
    return amount;
}

int FuelSystem::FuelBus::getBusNum() {
    return this->busNum;
}

void FuelSystem::FuelBus::setEfBusNum(int bNum) {
    this->efectiveBusNum = bNum;
}

int FuelSystem::FuelBus::getEfBusNum() {
    return this->efectiveBusNum;
}

void FuelSystem::FuelBus::setBusValves(FuelSystem::FuelBusValve **bValves, int nBValves) {
    this->busValvesList = (FuelBusValve**) malloc(nBValves * sizeof(FuelBusValve*));
    for (int i=0; i<nBValves; i++) {
        this->busValvesList[i] = bValves[i];
    }
    this->numBusValves = nBValves;
}

FuelSystem::FuelBusValve **FuelSystem::FuelBus::getBusValves() {
    return this->busValvesList;
}

int FuelSystem::FuelBus::getNumBusValves() {
    return this->numBusValves;
}

FuelSystem::FuelBus::~FuelBus() {
    free(this->pumpsList);
    free(this->tankValvesList);
    free(this->consumersList);
    free(this->busValvesList);
}
