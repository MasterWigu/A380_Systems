//
// Created by morei on 11/09/2020.
//

#include "PluginControl.h"
#include "../../include/SDK/CHeaders/XPLM/XPLMProcessing.h"

#include <cmath>

PlaneFuelSystem::SystemControl* systemControl;
PlaneFuelSystem::FQMS* fqms;

//NEEDED DATAREFS
XPLMDataRef TotaltFlightTimeSec;
XPLMDataRef TotalWeight;
XPLMDataRef CenterOfGravity;


//CUSTOM DATAREFS
XPLMDataRef Fuel_pumps;
XPLMDataRef Trim_valve;
XPLMDataRef Crossfeed_valves;
XPLMDataRef Transfer_valves;
XPLMDataRef Outlet_valves;
XPLMDataRef Emerg_valves;
XPLMDataRef Fuel_tank_quantities;
XPLMDataRef Fuel_on_board;
XPLMDataRef Jettison_valves;
XPLMDataRef Fuel_usage;
XPLMDataRef Tank_quantities_degraded;
XPLMDataRef Fuel_usage_degraded;
XPLMDataRef Memos_cross_open;
XPLMDataRef Memos_cross_open_abn;
XPLMDataRef Memos_cold_xfr;
XPLMDataRef Memos_fwd_xfr_prog;
XPLMDataRef Memos_jettison_prog;
XPLMDataRef Memos_outr_xfr_prog;
XPLMDataRef Memos_outr_xfrd;
XPLMDataRef Memos_trim_xfrd;


PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
    strcpy(outName, "A380 Fuel System");
    strcpy(outSig, "A380'Fuel System Plugin");
    strcpy(outDesc, "Plugin that manages all fuel transfers in the A380");

    //CREATE SYSTEM
    systemControl = new PlaneFuelSystem::SystemControl();
    fqms = systemControl->getFQMS();


    // CREATE DATAREFS

    Fuel_pumps = XPLMRegisterDataAccessor(

            "A380/fuel/fuel_pumps",
            xplmType_IntArray,          // The types we support
            1,                       // Writable
            NULL, NULL,              // Integer accessors
            NULL, NULL,              // Float accessors
            NULL, NULL,              // Doubles accessors
            GetFuelPumps, NULL,      // Int array accessors
            NULL, NULL,              // Float array accessors
            NULL, NULL,              // Raw data accessors
            NULL, NULL);             // Refcons not used

    Trim_valve = XPLMRegisterDataAccessor(

            "A380/fuel/trim_valve",
            xplmType_Int,          // The types we support
            1,                       // Writable
            GetTrimValve, NULL,              // Integer accessors
            NULL, NULL,              // Float accessors
            NULL, NULL,              // Doubles accessors
            NULL, NULL,      // Int array accessors
            NULL, NULL,              // Float array accessors
            NULL, NULL,              // Raw data accessors
            NULL, NULL);             // Refcons not used

    Crossfeed_valves = XPLMRegisterDataAccessor(

            "A380/fuel/crossfeed_valves",
            xplmType_IntArray,          // The types we support
            1,                       // Writable
            NULL, NULL,              // Integer accessors
            NULL, NULL,              // Float accessors
            NULL, NULL,              // Doubles accessors
            GetCrossfeedValves, NULL,      // Int array accessors
            NULL, NULL,              // Float array accessors
            NULL, NULL,              // Raw data accessors
            NULL, NULL);             // Refcons not used

    Transfer_valves = XPLMRegisterDataAccessor(

            "A380/fuel/transfer_valves",
            xplmType_IntArray,          // The types we support
            1,                       // Writable
            NULL, NULL,              // Integer accessors
            NULL, NULL,              // Float accessors
            NULL, NULL,              // Doubles accessors
            GetTransferValves, NULL,      // Int array accessors
            NULL, NULL,              // Float array accessors
            NULL, NULL,              // Raw data accessors
            NULL, NULL);             // Refcons not used

    Outlet_valves = XPLMRegisterDataAccessor(

            "A380/fuel/outlet_valves",
            xplmType_IntArray,          // The types we support
            1,                       // Writable
            NULL, NULL,              // Integer accessors
            NULL, NULL,              // Float accessors
            NULL, NULL,              // Doubles accessors
            GetOutletValves, NULL,      // Int array accessors
            NULL, NULL,              // Float array accessors
            NULL, NULL,              // Raw data accessors
            NULL, NULL);             // Refcons not used

    Emerg_valves = XPLMRegisterDataAccessor(

            "A380/fuel/emerg_valves",
            xplmType_IntArray,          // The types we support
            1,                       // Writable
            NULL, NULL,              // Integer accessors
            NULL, NULL,              // Float accessors
            NULL, NULL,              // Doubles accessors
            GetEmergValves, NULL,      // Int array accessors
            NULL, NULL,              // Float array accessors
            NULL, NULL,              // Raw data accessors
            NULL, NULL);             // Refcons not used



    Fuel_pumps = XPLMFindDataRef ("A380/fuel/fuel_pumps");
    //FlapSelectorPositionDataRef = XPLMFindDataRef ("BSUB/Aircraft/FlapSelectorPosition");


    //FlapRatioDataRef = XPLMFindDataRef("sim/cockpit2/controls/flap_ratio");
    TotaltFlightTimeSec = XPLMFindDataRef("sim/time/total_flight_time_sec");
    TotalWeight = XPLMFindDataRef("sim/flightmodel/weight/m_total");
    CenterOfGravity = XPLMFindDataRef("sim/flightmodel/misc/cgz_ref_to_default");


    //XPLMSetDataf(FlapPumpPositionDataRef, 0);
    //XPLMSetDataf(FlapSelectorPositionDataRef, 0);

    XPLMRegisterFlightLoopCallback(FuelSystemFLCB, 0.0, NULL);
    XPLMSetFlightLoopCallbackInterval(FuelSystemFLCB, 0.01, 1, NULL);

    return 1;
}

PLUGIN_API void	XPluginStop(void) {
    XPLMUnregisterDataAccessor(Fuel_pumps);
    XPLMUnregisterFlightLoopCallback(FuelSystemFLCB, NULL);
}


PLUGIN_API int XPluginEnable(void) {
    //TODO maybe find datarefs here?
    return 1;
}


PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, void* inParam) {}


int GetFuelPumps(void* inRefcon, int *out_val, int i_min, int i_max) {
    if(out_val == NULL)
        return 21;

    int r = 21 - i_min;
    if (r > i_max) r = 21;

    for(int i = 0; i < r; i++)
        out_val[i] = fqms->getPumpStateECAM(i);
    return r;
}

int GetTrimValve(void* inRefcon) {
    return 0;
}

int GetCrossfeedValves(void* inRefcon, int *out_val, int i_min, int i_max) {
    if(out_val == NULL)
        return 4;

    int r = 4 - i_min;
    if (r > i_max) r = 4;

    for(int i = 0; i < r; i++)
        out_val[i] = fqms->getPumpStateECAM(i);
    return r;
}

int GetTransferValves(void* inRefcon, int *out_val, int i_min, int i_max) {
    if(out_val == NULL)
        return 21;

    int r = 21 - i_min;
    if (r > i_max) r = 21;

    for(int i = 0; i < r; i++)
        out_val[i] = fqms->getPumpStateECAM(i);
    return r;
}

int GetOutletValves(void* inRefcon, int *out_val, int i_min, int i_max) {
    if(out_val == NULL)
        return 21;

    int r = 21 - i_min;
    if (r > i_max) r = 21;

    for(int i = 0; i < r; i++)
        out_val[i] = fqms->getPumpStateECAM(i);
    return r;
}

int GetEmergValves(void* inRefcon, int *out_val, int i_min, int i_max) {
    if(out_val == NULL)
        return 21;

    int r = 21 - i_min;
    if (r > i_max) r = 21;

    for(int i = 0; i < r; i++)
        out_val[i] = fqms->getPumpStateECAM(i);
    return r;
}

float FuelSystemFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon) {
    float simulatorTime = XPLMGetDataf(TotaltFlightTimeSec);
    int GW = (int) std::round(XPLMGetDataf(TotalWeight));
    float CGm = XPLMGetDataf(CenterOfGravity);

    double cgp = (CGm - 28.76405) / 0.12299; //TODO check if correct according to WBM and flight model

    //TODO read remaining flt minutes and FL from FMS when it is implemented
    systemControl->update(100, GW, cgp, simulatorTime, 100);
    return 0.1;
}