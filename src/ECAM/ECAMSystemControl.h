//
// Created by morei on 17/10/2020.
//

#ifndef A380_SYSTEMS_ECAMSYSTEMCONTROL_H
#define A380_SYSTEMS_ECAMSYSTEMCONTROL_H

#include "../FUEL/PlaneFuelSystem/FuelSystemFronend.h"
#include "PlaneSystemsRefs.h"

namespace ECAM {
    class ECAMSystemControl {
    private:
        PlaneSystemsRefs* planeSystems;
    public:
        ECAMSystemControl(Cockpit::CockpitControls* cC, PlaneFuelSystem::FuelSystemFronend* fFE);
    };
}


#endif //A380_SYSTEMS_ECAMSYSTEMCONTROL_H
