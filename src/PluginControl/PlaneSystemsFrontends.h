//
// Created by morei on 01/11/2020.
//

#ifndef A380_SYSTEMS_PLANESYSTEMSFRONTENDS_H
#define A380_SYSTEMS_PLANESYSTEMSFRONTENDS_H

#include "../FUEL/FuelSystemFrontend.h"
#include "../COCKPIT/CockpitControls.h"



namespace PluginControl {
    class PlaneSystemsFrontends {
    public:
        FuelSystem::FuelSystemFrontend* fuelSystemFe;
        Cockpit::CockpitControls* cockpitControls;
    };
}

#endif //A380_SYSTEMS_PLANESYSTEMSFRONTENDS_H
