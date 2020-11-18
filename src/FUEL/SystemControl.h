//
// Created by MasterWigu on 01/09/2020.
//

#ifndef A380_SYSTEMS_SYSTEMCONTROL_H
#define A380_SYSTEMS_SYSTEMCONTROL_H


#include "PhysicalFuelSystem/FuelSystem.h"
#include "PlaneFuelSystem/FQDC.h"
#include "PlaneFuelSystem/FQMS.h"

#include "../PluginControl/PlaneSystemsFrontends.h"

namespace FuelSystem {
    class SystemControl {
    private:
        PhysicalFuelSystem::FuelSystem* fuelSystem;
        PlaneFuelSystem::FQDC* fqdc;
        PlaneFuelSystem::FQMS* fqms;
        FuelSystemFrontend *frontend;

        PluginControl::PlaneSystemsFrontends* planeSysFEs;
    public:
        SystemControl();

        void update(int remMinutes, int GW, double currCG, float simulatorTime, int FL);
        PlaneFuelSystem::FQMS* getFQMS();
        FuelSystemFrontend* getFuelFrontend();

        void setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf);


    };

}


#endif //A380_SYSTEMS_SYSTEMCONTROL_H
