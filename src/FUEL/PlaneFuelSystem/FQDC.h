//
// Created by MasterWigu on 01/09/2020.
//

#ifndef A380_SYSTEMS_FQDC_H
#define A380_SYSTEMS_FQDC_H

#include "../PhysicalFuelSystem/FuelSystem.h"
#include <cmath>

namespace PlaneFuelSystem {
    class FQDC {
    private:
        PhysicalFuelSystem::FuelSystem* fuelSystem;
        bool AGPFailed;
    public:
        FQDC(PhysicalFuelSystem::FuelSystem* fS);

        int readQuantitySensorDirect(int id);

        int readQuantitySensorAGP(int id);

        void setAGPStatus(bool st);
        bool getAGPStatus();
    };
}

#endif //A380_SYSTEMS_FQDC_H
