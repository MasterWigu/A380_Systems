#include "PluginControl.h"


FuelSystem::SystemControl* systemControl;
PlaneFuelSystem::FQMS* fqms;

//NEEDED DATAREFS
XPLMDataRef TotaltFlightTimeSec;
XPLMDataRef TotalWeight;
XPLMDataRef CenterOfGravity;


//CUSTOM DATAREFS
//XPLMDataRef Fuel_pumps; *EXAMPLE*



PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
    strcpy(outName, "A380 Fuel System");
    strcpy(outSig, "A380'Fuel System Plugin");
    strcpy(outDesc, "Plugin that manages all fuel transfers in the A380");

    //CREATE SYSTEM
    systemControl = new FuelSystem::SystemControl();
    fqms = systemControl->getFQMS();


    // CREATE DATAREFS
    /* **** EXAMPLE ****
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
            */



    //FlapRatioDataRef = XPLMFindDataRef("sim/cockpit2/controls/flap_ratio");
    TotaltFlightTimeSec = XPLMFindDataRef("sim/time/total_flight_time_sec");
    TotalWeight = XPLMFindDataRef("sim/flightmodel/weight/m_total");
    CenterOfGravity = XPLMFindDataRef("sim/flightmodel/misc/cgz_ref_to_default");


    //XPLMSetDataf(FlapPumpPositionDataRef, 0);
    //XPLMSetDataf(FlapSelectorPositionDataRef, 0);

    XPLMRegisterFlightLoopCallback(A380SystemsFLCB, 0.0, NULL);
    XPLMSetFlightLoopCallbackInterval(A380SystemsFLCB, 0.01, 1, NULL);

    return 1;
}

PLUGIN_API void	XPluginStop(void) {
    //XPLMUnregisterDataAccessor(Fuel_pumps); ***EXAMPLE***
    XPLMUnregisterFlightLoopCallback(A380SystemsFLCB, NULL);
}


PLUGIN_API int XPluginEnable(void) {
    //Fuel_pumps = XPLMFindDataRef ("A380/fuel/fuel_pumps"); ***EXAMPLE***
    return 1;
}


PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, void* inParam) {}


float A380SystemsFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon) {
    float simulatorTime = XPLMGetDataf(TotaltFlightTimeSec);
    int GW = (int) std::round(XPLMGetDataf(TotalWeight));
    float CGm = XPLMGetDataf(CenterOfGravity);

    double cgp = (CGm - 28.76405) / 0.12299; //According to WBM

    systemControl->update(100, GW, cgp, simulatorTime, 100);
    return 0.1;
}