//
// Created by morei on 23/09/2020.
//

#ifndef A380_SYSTEMS_ECAMCALLBACKS_H
#define A380_SYSTEMS_ECAMCALLBACKS_H

#include "../../include/SDK/CHeaders/XPLM/XPLMDataAccess.h"
#include "../../include/SDK/CHeaders/XPLM/XPLMPlugin.h"
#include "../../include/SDK/CHeaders/XPLM/XPLMProcessing.h"

XPLMDataRef* FUELMEMOS;
XPLMDataRef* FUELPROC;

void lookupECAMDatarefs();

void setFuelMemo(int id, bool state);
void setFuelProc(int id, bool state);


#endif //A380_SYSTEMS_ECAMCALLBACKS_H
