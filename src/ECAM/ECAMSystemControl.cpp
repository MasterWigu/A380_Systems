//
// Created by morei on 17/10/2020.
//

#include "ECAMSystemControl.h"

namespace ECAM {
    void ECAMSystemControl::setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf) {
        this->planeSysFEs = psf;
    }

    void ECAMSystemControl::update() {

    }
}
