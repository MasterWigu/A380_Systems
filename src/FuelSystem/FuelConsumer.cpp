//
// Created by morei on 29/08/2020.
//

#include "FuelConsumer.h"

namespace FuelSystem {

    FuelConsumer::FuelConsumer(int r) {
        this->state = 0; // Starts closed
        this->rate = r;
        this->lastSupply = 0;
        this->isJettison = false;
    }

    FuelConsumer::FuelConsumer(int r, bool jet) {
        this->state = 0; // Starts closed
        this->rate = r;
        this->lastSupply = r;
        this->isJettison = jet;
    }

    void FuelConsumer::setRate(int rate) {
        this->rate = rate;
    }

    bool FuelConsumer::canConsume() {
        if (this->state == 1 && this->rate > 0) {
            return true;
        }
        return false;
    }

    int FuelConsumer::consume(int amount) {
        // if the amount is not enough, it will return negative (deficit)
        // only the jettison valves dont create deficits
        if (this->state == 1) {
            if (this->isJettison)
                return 0;

            if (amount > this->rate) // if supply was bigger than the rate, we consumed the rate, else we consumed all of it
                this->lastSupply = rate;
            else
                this->lastSupply = amount;
            return amount - this->rate;
        }
        return amount;
    }

    int FuelConsumer::getState() {
        return this->state;
    }

    void FuelConsumer::setState(int s) {
        this->state = s;
    }

    bool FuelConsumer::isFulfilled() {
        if (this->isJettison) return true;

        return this->lastSupply >= rate;
    }
}