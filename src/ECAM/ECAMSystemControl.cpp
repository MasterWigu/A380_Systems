//
// Created by morei on 17/10/2020.
//

#include "ECAMSystemControl.h"

namespace ECAM {
    ECAMSystemControl::ECAMSystemControl() {
        this->planeSysFEs = nullptr;

        this->frontend = new ECAMFrontend();
        this->ecamDataCache = new ECAMDataCache();

        this->fuelMonitor = new FuelMonitor(ecamDataCache);
    }

    void ECAMSystemControl::setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf) {
        this->planeSysFEs = psf;
    }

    PluginControl::PlaneSystemsFrontends *ECAMSystemControl::getPlaneSysFEs() const {
        return planeSysFEs;
    }

    ECAMFrontend *ECAMSystemControl::getEcamFrontend() {
        return this->frontend;
    }

    void ECAMSystemControl::update() {
        //TODO add systems here
        this->fuelMonitor->updateFrontend();

    }



}
