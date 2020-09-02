//
// Created by morei on 01/09/2020.
//

#ifndef A380_SYSTEMS_FQDC_H
#define A380_SYSTEMS_FQDC_H

#include "../FuelSystem/FuelSystem.h"

namespace PlaneFuelSystem {
    class FQDC {
    private:
        FuelSystem::FuelSystem* fuelSystem;
        bool AGPFailed;
    public:
        FQDC(FuelSystem::FuelSystem* fS);

        int readQuantitySensorDirect(int id);

        int readQuantitySensorAGP(int id);

        void setAGPStatus(bool st);
        bool getAGPStatus();
    };
}

#endif //A380_SYSTEMS_FQDC_H
