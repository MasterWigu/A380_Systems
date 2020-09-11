//
// Created by morei on 11/09/2020.
//

#ifndef A380_SYSTEMS_PLUGINCONTROL_H
#define A380_SYSTEMS_PLUGINCONTROL_H

#include <cmath>
#include "../../include/SDK/CHeaders/XPLM/XPLMDataAccess.h"
#include "../../include/SDK/CHeaders/XPLM/XPLMPlugin.h"
#include "../PlaneFuelSystem/SystemControl.h"

int GetFuelPumps(void* inRefcon, int *pInt, int i, int i1);
float FuelSystemFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);



#endif //A380_SYSTEMS_PLUGINCONTROL_H
