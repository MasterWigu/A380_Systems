//
// Created by morei on 28/08/2020.
//
#include <cmath>
#include "FuelBus.h"



FuelSystem::FuelBus::FuelBus(FuelSystem::FuelPump **pumps, int nPumps, FuelSystem::FuelTankValve **tankValves, int nTValves, FuelSystem::FuelConsumer** consumers, int nCons) {
    this->pumpsList = pumps;
    this->numPumps = nPumps;

    int tempArray[nPumps];
    this->pumpAmounts = tempArray;
    for (int i = 0; i<nPumps; i++)
        this->pumpAmounts[i] = 0;

    this->tankValvesList = tankValves;
    this->numTankValves = nTValves;

    int tempArray2[nTValves];
    this->gravFeedAmounts = tempArray2;
    for (int i = 0; i<nTValves; i++)
        this->gravFeedAmounts[i] = 0;

    this->consumersList = consumers;
    this->numConsumers = nCons;

    this->totalPumpGravFuel = 0;
}

int FuelSystem::FuelBus::getMaxAvail() {
    int availKg = 0;

    for (int i = 0; i<this->numPumps; i++) {
        this->pumpAmounts[i] = this->pumpsList[i]->getPumpable();
        availKg += this->pumpAmounts[i];
    }

    //only makes sense to get gravity feeding if no pump is on
    //if any pump is on, we dont check gravity feeding
    if (availKg > 0) {
        for (int i = 0; i< this->numTankValves; i++) {
            this->gravFeedAmounts[i] = 0;
        }
        this->totalPumpGravFuel = availKg;
        return availKg;
    }

    for (int i = 0; i<this->numTankValves; i++) {
        this->gravFeedAmounts[i] = this->tankValvesList[i]->getGravFeedable();
        availKg += this->gravFeedAmounts[i];
    }
    // TODO case in which the two main buses are connected (fuel made avail twice in mid and inner tanks)
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

    if (amount <= 1) // <5 instead of ==0 to compensate rounding errors
        return 0;
    for (int i=0; i<this->numTankValves; i++) {
        aux = (int)std::round(gravFeedAmounts[i]*percentage);
        amount -= aux;
        this->tankValvesList[i]->gravityFeed(aux);
    }
    return amount;
}
