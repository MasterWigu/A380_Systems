#ifndef A380_SYSTEMS_ECAMSYSTEMCONTROL_H
#define A380_SYSTEMS_ECAMSYSTEMCONTROL_H

#include "../FUEL/FuelSystemFrontend.h"
#include "../PluginControl/PlaneSystemsFrontends.h"
#include "ECAMFrontend.h"
#include "ECAMDataCache.h"
#include "FuelMonitor.h"

namespace ECAM {

    class ECAMSystemControl {
    private:
        ECAMFrontend* frontend;
        PluginControl::PlaneSystemsFrontends* planeSysFEs;
        ECAMDataCache* ecamDataCache;

        FuelMonitor* fuelMonitor;

    public:
        ECAMSystemControl();

        PluginControl::PlaneSystemsFrontends *getPlaneSysFEs() const;
        void setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf);
        ECAMFrontend* getEcamFrontend();

        void update();
    };
}


#endif //A380_SYSTEMS_ECAMSYSTEMCONTROL_H
