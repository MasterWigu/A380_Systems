//
// Created by morei on 01/11/2020.
//

#include "SystemsControl.h"



namespace PluginControl {

    SystemsControl::SystemsControl(SimulatorData* sD) {
        this->simulatorData = sD;
        this->systemsInstantiated = false;
        this->planeSystems = nullptr;
    }

    void SystemsControl::createSystems() {
        //Create all systems

        Cockpit::CockpitControls* cC = new Cockpit::CockpitControls();
        FuelSystem::SystemControl* fS = new FuelSystem::SystemControl();
        ECAM::ECAMSystemControl* eS = new ECAM::ECAMSystemControl();



        //Create SystemsRefs
        PlaneSystemsRefs* planeRefs = new PlaneSystemsRefs();
        planeRefs->cockpitControls = cC;
        planeRefs->fuelSystem = fS;
        planeRefs->ecamSystem = eS;

        //Create systems frontends
        PlaneSystemsFrontends* planeFEnds = new PlaneSystemsFrontends();
        planeFEnds->cockpitControls = cC;
        planeFEnds->fuelSystemFe = fS->getFuelFrontend();


        //Inform systems of the frontends
        fS->setPlaneFrontends(planeFEnds);
        eS->setPlaneFrontends(planeFEnds);

        this->planeSystems = planeRefs;
        this->systemsInstantiated = true;
    }

    void SystemsControl::updateAllSystems() {

        this->planeSystems->fuelSystem->update(100, simulatorData->getPlaneGw(), simulatorData->getPlaneCurrCg(), simulatorData->getSimulatorTime(), simulatorData->getFl());
        this->planeSystems->ecamSystem->update();
    }
}