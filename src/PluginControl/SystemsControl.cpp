#include "SystemsControl.h"



namespace PluginControl {

    SystemsControl::SystemsControl() {
        this->simulatorData = nullptr;
        this->systemsInstantiated = false;
        this->planeSystems = nullptr;
    }

    void SystemsControl::createSystems() {
        //Initialize part of the PluginControl System
        this->simulatorData = new SimulatorData();



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
        planeFEnds->simulatorData = this->simulatorData;
        planeFEnds->cockpitControls = cC;
        planeFEnds->fuelSystemFe = fS->getFuelFrontend();
        planeFEnds->ecamFe = eS->getEcamFrontend();


        //Inform systems of the frontends
        fS->setPlaneFrontends(planeFEnds);
        eS->setPlaneFrontends(planeFEnds);

        //Create data handlers and inform them of where are the systems
        this->cockpitDataHandlers = new COCKPIT_DataHandlers(cC);
        this->ecamDataHandlers = new ECAM_DataHandlers(eS->getEcamFrontend());
        this->fuelDataHandlers = new FUEL_DataHandlers(fS->getFuelFrontend());
        this->xplaneDataHandlers = new XPLANE_DataHandlers(this->simulatorData);


        this->planeSystems = planeRefs;
        this->systemsInstantiated = true;
    }

    void SystemsControl::enablePlugin() {

    }

    void SystemsControl::updateAllSystems() {
        this->xplaneDataHandlers->readAll(); //update the simulator data cache

        this->planeSystems->fuelSystem->update(100, simulatorData->getPlaneGw(), simulatorData->getPlaneCurrCg(), simulatorData->getSimulatorTime(), simulatorData->getFl());
        this->planeSystems->ecamSystem->update();

    }

}