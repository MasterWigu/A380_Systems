//
// Created by morei on 17/10/2020.
//

#include "ECAMSystemControl.h"

namespace ECAM {
    ECAMSystemControl::ECAMSystemControl(Cockpit::CockpitControls* cC, PlaneFuelSystem::FuelSystemFronend *fFE) {
        this->planeSystems = new PlaneSystemsRefs(cC, fFE);
        //TODO add other systems here as argument
    }

}
