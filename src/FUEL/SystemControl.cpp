#include "SystemControl.h"


namespace FuelSystem {
    FuelSystem::SystemControl::SystemControl() {
        this->fuelSystem = new PhysicalFuelSystem::FuelSystem();  //create the physical system
        this->fqdc = new PlaneFuelSystem::FQDC(this->fuelSystem); // create the fqdc
        this->frontend = new FuelSystem::FuelSystemFrontend(); // create the frontend
        this->fqms = new PlaneFuelSystem::FQMS(this->fuelSystem, this->fqdc, this->frontend); //initialize the FQMS
    }

    void SystemControl::update(int remMinutes, int GW, double currCG, float simulatorTime, int FL) {
        // all this args should be migrated to frontends
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