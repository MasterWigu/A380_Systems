#include "XPLANE_DataHandlers.h"

XPLANE_DataHandlers::XPLANE_DataHandlers(PluginControl::SimulatorData *sD) {
    this->simulatorData = sD;
}

void XPLANE_DataHandlers::readAll() {

}


//Formula for converting CG in meters to CG in %MAC
//double cgp = (CGm - 28.76405) / 0.12299; //According to WBM