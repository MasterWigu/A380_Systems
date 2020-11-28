#ifndef A380SYSTEMS_COCKPIT_DATAHANDLERS_H
#define A380SYSTEMS_COCKPIT_DATAHANDLERS_H

#include "../../COCKPIT/CockpitControls.h"
/// @class COCKPIT_DataHandlers is the class that handles all dataref callbacks related to the cockpit. It will read/write to the Cockpit Controls class.
class COCKPIT_DataHandlers {
private:
    Cockpit::CockpitControls* cockpitControls;

public:
    explicit COCKPIT_DataHandlers(Cockpit::CockpitControls* cC);

    /// Function to register the datarefs in XPlane
    void registerDatarefs();

    /// Function to search for the datarefs we created in this class, to check if they are working
    void searchRegisteredDatarefs();
};


#endif //A380SYSTEMS_COCKPIT_DATAHANDLERS_H
