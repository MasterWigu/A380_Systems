//
// Created by morei on 17/10/2020.
//

#ifndef A380_SYSTEMS_PLANESYSTEMSREFS_H
#define A380_SYSTEMS_PLANESYSTEMSREFS_H

#include "../FUEL/PlaneFuelSystem/SystemControl.h"
#include "../COCKPIT/CockpitControls.h"

namespace ECAM {
    class PlaneSystemsRefs {
    public:
        PlaneFuelSystem::FuelSystemFronend* fuelSystem;
        Cockpit::CockpitControls* cockpitControls;

        PlaneSystemsRefs(Cockpit::CockpitControls* cC, PlaneFuelSystem::FuelSystemFronend* fFE);
    };
}


#endif //A380_SYSTEMS_PLANESYSTEMSREFS_H
