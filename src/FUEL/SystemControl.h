//
// Created by MasterWigu on 01/09/2020.
//

#ifndef A380_SYSTEMS_SYSTEMCONTROL_H
#define A380_SYSTEMS_SYSTEMCONTROL_H


#include "PhysicalFuelSystem/FuelSystem.h"
#include "PlaneFuelSystem/FQDC.h"
#include "PlaneFuelSystem/FQMS.h"

#include "../PluginControl/PlaneSystemsFrontends.h"

namespace FuelSystem {

    /// @class SystemControl is responsible for the initialization of the whole fuel system (physical and plane)
    /// It is responsible to get and store the communication frontends of the other systems
    /// It is also responsible to trigger system updates when the update function is called here
    class SystemControl {
    private:
        PhysicalFuelSystem::FuelSystem* fuelSystem;
        PlaneFuelSystem::FQDC* fqdc;
        PlaneFuelSystem::FQMS* fqms;
        FuelSystemFrontend *frontend;

        PluginControl::PlaneSystemsFrontends* planeSysFEs;
    public:

        /// Initializes the whole fuel system
        SystemControl();

        /// Triggers an update of the whole system, from the tank levels to the FQMS
        /// The params should later be relocated to frontends of other systems
        void update(int remMinutes, int GW, double currCG, float simulatorTime, int FL);

        /// Function to get the pointer to the FQMS
        /// @return the instance of the FQMS
        PlaneFuelSystem::FQMS* getFQMS();

        /// Function to get the pointer to the fuel system frontend
        /// @return the instance of the fuel system frontend
        FuelSystemFrontend* getFuelFrontend();

        /// Sets the frontends of all the systems in the plane, for inter-system communication
        /// @param [in] psf - the pointer to the plane systems frontends (all of them)
        void setPlaneFrontends(PluginControl::PlaneSystemsFrontends* psf);
    };

}


#endif //A380_SYSTEMS_SYSTEMCONTROL_H
