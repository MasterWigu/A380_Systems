//
// Created by MasterWigu on 17/10/2020.
//

#ifndef A380_SYSTEMS_F001_ALLFEEDLOW_H
#define A380_SYSTEMS_F001_ALLFEEDLOW_H

#include "ECAMProcedure.h"
#include "../../PluginControl/PlaneSystemsRefs.h"

namespace ECAM {
    class F001_AllFeedLow: ECAMProcedure {
    public:
        char* line1Under;
        int* lineColors;
        char** linesBefore;
        char** linesAfter;

        char** limitations;

        ProcDisplayData* displayData;
        ProcPermInfo* permInfo;
        PluginControl::PlaneSystemsRefs* planeSystems;

        F001_AllFeedLow(PluginControl::PlaneSystemsRefs* systems);
        bool showProcedure(int linesToShow, bool selected, bool lastLineTicked);

        bool testProcedure();
        bool getPermInfo();
    };

}


#endif //A380_SYSTEMS_F001_ALLFEEDLOW_H
