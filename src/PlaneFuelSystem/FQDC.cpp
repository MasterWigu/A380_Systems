//
// Created by morei on 01/09/2020.
//

#include "FQDC.h"

namespace PlaneFuelSystem {
    FQDC::FQDC(FuelSystem::FuelSystem *fS) {
        this->fuelSystem = fS;
        this->AGPFailed = false;
    }

    int FQDC::readQuantitySensorDirect(int id) {
        return this->fuelSystem->readQuantity(id);
    }

    int FQDC::readQuantitySensorAGP(int id) {
        if (!this->AGPFailed) {
            return this->readQuantitySensorDirect(id);
        }
        return 0; //Simulates AGP failure
    }

    void FQDC::setAGPStatus(bool st) {
        this->AGPFailed = st;
    }

    bool FQDC::getAGPStatus() {
        return this->AGPFailed;
    }
}