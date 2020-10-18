//
// Created by morei on 17/10/2020.
//

#include "PlaneSystemsRefs.h"

namespace ECAM {
    PlaneSystemsRefs::PlaneSystemsRefs(Cockpit::CockpitControls* cC, PlaneFuelSystem::FuelSystemFronend *fFE) {
        this->cockpitControls = cC;
        this->fuelSystem = fFE;
    }
}
