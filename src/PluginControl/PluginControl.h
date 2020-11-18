//
// Created by MasterWigu on 11/09/2020.
//

#ifndef A380_SYSTEMS_PLUGINCONTROL_H
#define A380_SYSTEMS_PLUGINCONTROL_H

#include <cmath>
#include "../../include/SDK/CHeaders/XPLM/XPLMDataAccess.h"
#include "../../include/SDK/CHeaders/XPLM/XPLMPlugin.h"
#include "../../include/SDK/CHeaders/XPLM/XPLMProcessing.h"

#include "../FUEL/SystemControl.h"




int GetFuelPumps(void* inRefcon, int *out_val, int i_min, int i_max);
int GetTrimValve(void* inRefcon);
int GetCrossfeedValves(void* inRefcon, int *out_val, int i_min, int i_max);
int GetTransferValves(void* inRefcon, int *out_val, int i_min, int i_max);
int GetOutletValves(void* inRefcon, int *out_val, int i_min, int i_max);
int GetEmergValves(void* inRefcon, int *out_val, int i_min, int i_max);


float FuelSystemFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);



#endif //A380_SYSTEMS_PLUGINCONTROL_H
