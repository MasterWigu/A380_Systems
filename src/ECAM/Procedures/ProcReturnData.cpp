//
// Created by morei on 17/10/2020.
//

#include <cstdlib>
#include "ProcReturnData.h"


namespace ECAM {

    ProcDisplayData::ProcDisplayData() {
        this->active = false;
        this->inhibited = false;
        this->cleared = false;

        this->numberLines = 0;
        this->overflow = false;
        this->selectedLine = 0;
        this->sdPage = -1;
        this->sound = -1;

        this->lineColors = (int*) malloc(18*sizeof(int));
        this->line1Box = nullptr;
        this->line1Under = nullptr;
        this->linesText = (char**) malloc(18*sizeof(char*)); //max return 18 lines
    }

    ProcPermInfo::ProcPermInfo() {
        this->active = false;
        this->memos            = (int*) malloc(3*sizeof(int)); //assume no more than 3 memos per procedure
        this->ecamLimitAll     = (char**) malloc(10*sizeof(char*)); //assume no more than 10 limitations per procedure
        this->ecamLimitApprLdg = (char**) malloc(10*sizeof(char*));
        this->inopAll          = (char**) malloc(10*sizeof(char*)); //assume no more than 10 inops per procedure
        this->inopApprLdg      = (char**) malloc(10*sizeof(char*));
        this->nMemos = 0;
        this->nEcamLimitAll = 0;
        this->nEcamLimitApprLdg = 0;
        this->nInopAll = 0;
        this->nInopApprLdg = 0;
    }
}