#ifndef A380_SYSTEMS_SYSTEMSCONTROL_H
#define A380_SYSTEMS_SYSTEMSCONTROL_H

#include "../FUEL/SystemControl.h"
#include "../ECAM/ECAMSystemControl.h"
#include "../COCKPIT/CockpitControls.h"

#include "DatarefHandlers/COCKPIT_DataHandlers.h"
#include "DatarefHandlers/ECAM_DataHandlers.h"
#include "DatarefHandlers/FUEL_DataHandlers.h"
#include "DatarefHandlers/XPLANE_DataHandlers.h"

#include "PlaneSystemsRefs.h"
#include "PlaneSystemsFrontends.h"
#include "SimulatorData.h"

namespace PluginControl {
    class SystemsControl {
    private:
        COCKPIT_DataHandlers* cockpitDataHandlers;
        ECAM_DataHandlers* ecamDataHandlers;
        FUEL_DataHandlers* fuelDataHandlers;
        XPLANE_DataHandlers* xplaneDataHandlers;

        PlaneSystemsRefs* planeSystems;
        SimulatorData* simulatorData;
        bool systemsInstantiated;
    public:
        SystemsControl();

        void createSystems();

        void enablePlugin();

        void updateAllSystems();
    };
}

#endif //A380_SYSTEMS_SYSTEMSCONTROL_H
