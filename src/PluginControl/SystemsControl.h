#ifndef A380_SYSTEMS_SYSTEMSCONTROL_H
#define A380_SYSTEMS_SYSTEMSCONTROL_H

#include "../FUEL/SystemControl.h"
#include "../ECAM/ECAMSystemControl.h"
#include "../COCKPIT/CockpitControls.h"

#include "PlaneSystemsRefs.h"
#include "PlaneSystemsFrontends.h"
#include "SimulatorData.h"

namespace PluginControl {
    class SystemsControl {
    private:
        PlaneSystemsRefs* planeSystems;
        SimulatorData* simulatorData;
        bool systemsInstantiated;
    public:
        SystemsControl(SimulatorData* sD);

        void createSystems();

        void updateAllSystems();
    };
}

#endif //A380_SYSTEMS_SYSTEMSCONTROL_H
