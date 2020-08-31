//
// Created by morei on 29/08/2020.
//

#include "FuelConsumer.h"

namespace FuelSystem {

    FuelConsumer::FuelConsumer(int r) {
        this->state = 0; // Starts closed
        this->commandedState = 0;
        this->rate = r;
        this->lastSupply = 0;
        this->isJettison = false;
        this->isPowered = false;
    }

    FuelConsumer::FuelConsumer(int r, bool jet) {
        this->state = 0; // Starts closed
        this->rate = r;
        this->lastSupply = r;
        this->isJettison = jet;
        this->isPowered = false;
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
        this->commandedState = s;
        if (this->isPowered) //if the valve is not powered, cant change state
            this->state = s;
    }

    bool FuelConsumer::isFulfilled() {
        if (this->isJettison) return true;

        return this->lastSupply >= rate;
    }

    void FuelConsumer::setPower(bool p) {
        this->isPowered = p;
        if (p) // when it gets power again, we revert state to the correct one
            this->state = this->commandedState;
    }

    bool FuelConsumer::getPower() {
        return this->isPowered;
    }
}