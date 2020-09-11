//
// Created by morei on 01/09/2020.
//

#include "SystemControl.h"


namespace PlaneFuelSystem {


    PlaneFuelSystem::SystemControl::SystemControl() {
        this->fuelSystem = new FuelSystem::FuelSystem();
        this->fqdc = new PlaneFuelSystem::FQDC(this->fuelSystem);
        this->fqms = new PlaneFuelSystem::FQMS(this->fuelSystem, this->fqdc);
    }

    void SystemControl::update(int remMinutes, int GW, double currCG, float simulatorTime) {
        this->fuelSystem->update(simulatorTime);
        this->fqms->updateLoop(remMinutes, GW, currCG);
    }

    FQMS* SystemControl::getFQMS() {
        return this->fqms;
    }


}