//
// Created by morei on 17/10/2020.
//

#include "FuelSystemFronend.h"

namespace PlaneFuelSystem {
    double *FuelSystemFronend::getTankLevels() {
        return this->tankLevels;
    }

    void FuelSystemFronend::setTankLevels(double *levels) {
        for (int i=0; i<15; i++)
            this->tankLevels[i] = levels[i];
    }

}