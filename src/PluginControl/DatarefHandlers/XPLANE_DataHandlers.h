#ifndef A380SYSTEMS_XPLANE_DATAHANDLERS_H
#define A380SYSTEMS_XPLANE_DATAHANDLERS_H

#include "../SimulatorData.h"

/// @class XPLANE_DataHandlers is the class that handles all reads and writes to default XPLANE datarefs.
/// The data it READS will be cached in the SimulatorData class.
/// It will write data that it gets from the various systems frontends.
class XPLANE_DataHandlers {
private:
    PluginControl::SimulatorData* simulatorData;
public:
    explicit XPLANE_DataHandlers(PluginControl::SimulatorData* sD);

    /// Function to read all needed datarefs from Xplane and write them in the simulator data class
    void readAll();
};


#endif //A380SYSTEMS_XPLANE_DATAHANDLERS_H
