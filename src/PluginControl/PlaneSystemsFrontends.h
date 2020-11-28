#ifndef A380_SYSTEMS_PLANESYSTEMSFRONTENDS_H
#define A380_SYSTEMS_PLANESYSTEMSFRONTENDS_H

#include "../FUEL/FuelSystemFrontend.h"
#include "../COCKPIT/CockpitControls.h"
#include "../ECAM/ECAMFrontend.h"
#include "SimulatorData.h"

namespace PluginControl {

    /// @class PlaneSystemsFrontends is the class that aggregates the references for all system's communication endpoints.
    /// After being populated, a reference to a single instance of this class is to be distributed to all systems.
    /// (this class is a singleton)
    class PlaneSystemsFrontends {
    public:
        ECAM::ECAMFrontend* ecamFe;
        FuelSystem::FuelSystemFrontend* fuelSystemFe;
        Cockpit::CockpitControls* cockpitControls;
        SimulatorData* simulatorData;

        //NOTE: When adding systems (refs) here do not forget to assign them in SystemsControl!!!
    };
}

#endif //A380_SYSTEMS_PLANESYSTEMSFRONTENDS_H
