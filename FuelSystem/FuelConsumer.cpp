//
// Created by morei on 29/08/2020.
//

#include "FuelConsumer.h"

namespace FuelSystem {

    FuelConsumer::FuelConsumer(int r) {
        this->state = 0; // Starts closed
        this->rate = r;
        this->isJettison = false;
    }

    FuelConsumer::FuelConsumer(int r, bool jet) {
        this->state = 0; // Starts closed
        this->rate = r;
        this->isJettison = jet;
    }

    void FuelConsumer::setRate(int rate) {
        this->rate = rate;
    }

    bool FuelConsumer::canConsume() const {
        if (this->state == 1 && this->rate > 0) {
            return true;
        }
        return false;
    }

    int FuelConsumer::consume(int amount) const {
        // if the amount is not enough, it will return negative (deficit)
        // only the jettison valves dont create deficits
        if (this->state == 1) {
            if (this->isJettison)
                return 0;
            return amount - this->rate;
        }
        return amount;
    }

    int FuelConsumer::getState() const {
        return this->state;
    }

    void FuelConsumer::setState(int s) {
        this->state = s;
    }
}