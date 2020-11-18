//
// Created by MasterWigu on 01/09/2020.
//

#include "SystemControl.h"


namespace FuelSystem {
    FuelSystem::SystemControl::SystemControl() {
        this->fuelSystem = new PhysicalFuelSystem::FuelSystem();
        this->fqdc = new PlaneFuelSystem::FQDC(this->fuelSystem);
        this->frontend = new FuelSystem::FuelSystemFrontend();
        this->fqms = new PlaneFuelSystem::FQMS(this->fuelSystem, this->fqdc, this->frontend);
    }

    void SystemControl::update(int remMinutes, int GW, double currCG, float simulatorTime, int FL) {
        this->fuelSystem->update(simulatorTime);
        this->fqms->updateLoop(remMinutes, GW, currCG, simulatorTime, FL);
    }

    PlaneFuelSystem::FQMS* SystemControl::getFQMS() {
        return this->fqms;
    }

    FuelSystemFrontend* SystemControl::getFuelFrontend() {
        return this->frontend;
    }

    void SystemControl::setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf) {
        this->planeSysFEs = psf;
    }


}