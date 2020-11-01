//
// Created by morei on 17/10/2020.
//

#ifndef A380_SYSTEMS_ECAMSYSTEMCONTROL_H
#define A380_SYSTEMS_ECAMSYSTEMCONTROL_H

#include "../FUEL/FuelSystemFrontend.h"
#include "../PluginControl/PlaneSystemsFrontends.h"

namespace ECAM {

    class ECAMSystemControl {
    public:
        PluginControl::PlaneSystemsFrontends* planeSysFEs;


        void setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf);

        void update();
    };
}


#endif //A380_SYSTEMS_ECAMSYSTEMCONTROL_H
