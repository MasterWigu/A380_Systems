//
// Created by morei on 17/10/2020.
//

#ifndef A380_SYSTEMS_PROCRETURNDATA_H
#define A380_SYSTEMS_PROCRETURNDATA_H

namespace ECAM {
    class ProcDisplayData {
    public:
        bool active;
        bool inhibited;
        bool cleared;

        int numberLines;
        bool overflow;
        int selectedLine;
        int sdPage;
        int sound;

        int* lineColors;
        char* line1Box;
        char* line1Under;
        char** linesText;

        ProcDisplayData();
    };

    class ProcPermInfo {
    public:
        bool active;

        int* memos;
        int nMemos;
        char** ecamLimitAll;
        int nEcamLimitAll;
        char** ecamLimitApprLdg;
        int nEcamLimitApprLdg;
        char** inopAll;
        int nInopAll;
        char** inopApprLdg;
        int nInopApprLdg;

        ProcPermInfo();
    };
}


#endif //A380_SYSTEMS_PROCRETURNDATA_H
