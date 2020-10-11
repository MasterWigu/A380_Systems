//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_TRIMINNER_H
#define A380_SYSTEMS_TRIMINNER_H

#include "Template.h"

namespace PlaneFuelSystem {
    class TrimInner: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        TrimInner();
        ~TrimInner();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };

}


#endif //A380_SYSTEMS_TRIMINNER_H
