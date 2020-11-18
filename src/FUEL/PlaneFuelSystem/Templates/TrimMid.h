//
// Created by MasterWigu on 08/09/2020.
//

#ifndef A380_SYSTEMS_TRIMMID_H
#define A380_SYSTEMS_TRIMMID_H

#include "Template.h"

namespace PlaneFuelSystem {
    class TrimMid: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        TrimMid();
        ~TrimMid();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}


#endif //A380_SYSTEMS_TRIMMID_H
