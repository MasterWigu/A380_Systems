//
// Created by MasterWigu on 17/10/2020.
//

#ifndef A380_SYSTEMS_PLANESYSTEMSREFS_H
#define A380_SYSTEMS_PLANESYSTEMSREFS_H

#include "../FUEL/SystemControl.h"
#include "../COCKPIT/CockpitControls.h"
#include "../ECAM/ECAMSystemControl.h"

namespace PluginControl {
    class PlaneSystemsRefs {
    public:
        FuelSystem::SystemControl* fuelSystem;
        ECAM::ECAMSystemControl* ecamSystem;
        Cockpit::CockpitControls* cockpitControls;

    };
}


#endif //A380_SYSTEMS_PLANESYSTEMSREFS_H
