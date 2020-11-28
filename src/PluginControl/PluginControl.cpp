#include "PluginControl.h"

PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
    strcpy(outName, "J-PRO A380 Systems");
    strcpy(outSig, "J-PRO A380 Systems Plugin");
    strcpy(outDesc, "Plugin that manages all systems of the J-PRO's A380");

    //CREATE SYSTEM
    systemsControl = new PluginControl::SystemsControl();
    systemsControl->createSystems();

    XPLMRegisterFlightLoopCallback(A380SystemsFLCB, 0.0, NULL);
    XPLMSetFlightLoopCallbackInterval(A380SystemsFLCB, 0.01, 1, NULL);

    return 1;
}

PLUGIN_API void	XPluginStop(void) {
    XPLMUnregisterFlightLoopCallback(A380SystemsFLCB, NULL);
}


PLUGIN_API int XPluginEnable(void) {
    systemsControl->enablePlugin();
    return 1;
}


PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, void* inParam) {}


float A380SystemsFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon) {
    systemsControl->updateAllSystems();
    return 0.1;
}