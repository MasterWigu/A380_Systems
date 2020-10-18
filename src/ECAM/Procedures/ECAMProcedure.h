//
// Created by morei on 10/10/2020.
//

#ifndef A380_SYSTEMS_ECAMPROCEDURE_H
#define A380_SYSTEMS_ECAMPROCEDURE_H

#include "ProcReturnData.h"

namespace ECAM {

    class ECAMProcedure {
    public:
        //calculates procedure, returns true only if there is something that the ecam should display
        virtual bool showProcedure(int linesToShow, bool selected, bool lastLineTicked) = 0;
        virtual bool testProcedure() = 0;
        virtual bool getPermInfo() = 0;
    };
}

#endif //A380_SYSTEMS_ECAMPROCEDURE_H
