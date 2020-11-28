
#ifndef A380SYSTEMS_FUEL_DATAHANDLERS_H
#define A380SYSTEMS_FUEL_DATAHANDLERS_H

#include "../../FUEL/FuelSystemFrontend.h"

/// @class FUEL_DataHandlers is the class that handles all dataref callbacks related to the fuel system. It will read from the FUEL Frontend.
class FUEL_DataHandlers {
private:
    FuelSystem::FuelSystemFrontend* fuelFrontend;
public:
    explicit FUEL_DataHandlers(FuelSystem::FuelSystemFrontend* fsFe);

    /// Function to register the datarefs in XPlane
    void registerDatarefs();

    /// Function to search for the datarefs we created in this class, to check if they are working
    void searchRegisteredDatarefs();

};


#endif //A380SYSTEMS_FUEL_DATAHANDLERS_H
