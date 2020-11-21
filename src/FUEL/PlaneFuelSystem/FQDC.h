//
// Created by MasterWigu on 01/09/2020.
//

#ifndef A380_SYSTEMS_FQDC_H
#define A380_SYSTEMS_FQDC_H

#include "../PhysicalFuelSystem/FuelSystem.h"
#include <cmath>

namespace PlaneFuelSystem {
    /// @class FQDC simulates the real plane's FQDC
    /// It is responsible for the reading of the quantities of fuel in the tanks
    class FQDC {
    private:
        PhysicalFuelSystem::FuelSystem* fuelSystem;
        bool AGPFailed;
    public:

        /// Instantiates the FQDC
        /// @param [in] fS - the physical fuel system
        FQDC(PhysicalFuelSystem::FuelSystem* fS);

        /// Read the fuel quantity in the specified tank directly (independent of FQDC or AGP failure)
        /// @param [in] id - the id of the tank
        /// @return the quantity of fuel in the tank (kg)
        int readQuantitySensorDirect(int id);

        /// Read the fuel quantity in the specified tank through the FQDC & AGP (dependent of FQDC or AGP failure)
        /// @param [in] id - the id of the tank
        /// @return the quantity of fuel in the tank (kg)
        int readQuantitySensorAGP(int id);

        /// Sets the AGP status (failed or working)
        /// @param [in] st - new status (false = failed; true = working)
        void setAGPStatus(bool st);

        /// Gets the AGP status (failed or working)
        /// @return the status of the AGP (false = failed; true = working)
        bool getAGPStatus();
    };
}

#endif //A380_SYSTEMS_FQDC_H
