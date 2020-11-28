#ifndef A380SYSTEMS_ECAM_DATAHANDLERS_H
#define A380SYSTEMS_ECAM_DATAHANDLERS_H

#include "../../ECAM/ECAMFrontend.h"

/// @class ECAM_DataHandlers is the class that handles all dataref callbacks related to the ECAM system. It will read from the ECAM Frontend.
class ECAM_DataHandlers {
private:
    ECAM::ECAMFrontend* ecamFrontend;
public:
    explicit ECAM_DataHandlers(ECAM::ECAMFrontend* eFe);

    /// Function to register the datarefs in XPlane
    void registerDatarefs();

    /// Function to search for the datarefs we created in this class, to check if they are working
    void searchRegisteredDatarefs();


};


#endif //A380SYSTEMS_ECAM_DATAHANDLERS_H
