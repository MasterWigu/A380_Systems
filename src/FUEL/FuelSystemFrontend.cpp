//
// Created by morei on 17/10/2020.
//

#include "FuelSystemFrontend.h"

namespace FuelSystem {
    double *FuelSystemFrontend::getTankLevels() {
        return this->tankLevels;
    }

    void FuelSystemFrontend::setTankLevels(double *levels) {
        for (int i=0; i<15; i++)
            this->tankLevels[i] = levels[i];
    }

}