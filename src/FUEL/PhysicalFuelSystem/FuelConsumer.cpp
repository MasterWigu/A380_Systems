#include "FuelConsumer.h"

namespace PhysicalFuelSystem {

    FuelConsumer::FuelConsumer(double r, bool jet) {
        this->state = 0; // Starts closed
        this->rate = r;
        this->lastSupply = r;
        this->isJettison = jet;
        this->isPowered = false;
    }

    void FuelConsumer::setRate(double r) {
        this->rate = r;
    }

    bool FuelConsumer::canConsume() {
        if (this->state == 1 && this->rate > 0) {
            return true;
        }
        return false;
    }

    double FuelConsumer::consume(double amount, float deltaTime) {
        // if the amount is not enough, it will return negative (deficit)
        // only the jettison valves dont create deficits

        //calculate needed fuel
        double neededFuel = (this->rate/ 60.0) * deltaTime;

        if (this->state == 1) {
            if (this->isJettison)
                return 0;

            if (amount > neededFuel) // if supply was bigger than the rate, we consumed the rate, else we consumed all of it
                this->lastSupply = neededFuel;
            else
                this->lastSupply = amount;
            return amount - neededFuel;
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