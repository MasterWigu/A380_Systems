#ifndef A380_SYSTEMS_PLUGINCONTROL_H
#define A380_SYSTEMS_PLUGINCONTROL_H

#include <cmath>
#include "../../include/XPSDK303/CHeaders/XPLM/XPLMDataAccess.h"
#include "../../include/XPSDK303/CHeaders/XPLM/XPLMPlugin.h"
#include "../../include/XPSDK303/CHeaders/XPLM/XPLMProcessing.h"

#include "SystemsControl.h"

PluginControl::SystemsControl* systemsControl;

float A380SystemsFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);

#endif //A380_SYSTEMS_PLUGINCONTROL_H
