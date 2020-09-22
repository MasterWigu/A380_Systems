//
// Created by morei on 01/09/2020.
//

#ifndef A380_SYSTEMS_SYSTEMCONTROL_H
#define A380_SYSTEMS_SYSTEMCONTROL_H
#include "../FuelSystem/FuelSystem.h"
#include "FQDC.h"
#include "FQMS.h"


namespace PlaneFuelSystem {
    class SystemControl {
    private:
        FuelSystem::FuelSystem* fuelSystem;
        PlaneFuelSystem::FQDC* fqdc;
        PlaneFuelSystem::FQMS* fqms;
    public:
        SystemControl();

        void update(int remMinutes, int GW, double currCG, float simulatorTime, int FL);
        FQMS* getFQMS();
    };

}


#endif //A380_SYSTEMS_SYSTEMCONTROL_H
