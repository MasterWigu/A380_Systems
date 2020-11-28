#ifndef A380_SYSTEMS_PLANESYSTEMSREFS_H
#define A380_SYSTEMS_PLANESYSTEMSREFS_H

#include "../FUEL/SystemControl.h"
#include "../COCKPIT/CockpitControls.h"
#include "../ECAM/ECAMSystemControl.h"

namespace PluginControl {

    /// @class PlaneSystemsRefs is the class that aggregates the references for all system's control endpoints.
    /// This is used only by the PluginControl module to keep control of all plane's systems.
    /// (this class is a singleton)
    class PlaneSystemsRefs {
    public:
        FuelSystem::SystemControl* fuelSystem;
        ECAM::ECAMSystemControl* ecamSystem;
        Cockpit::CockpitControls* cockpitControls;

    };
}


#endif //A380_SYSTEMS_PLANESYSTEMSREFS_H
