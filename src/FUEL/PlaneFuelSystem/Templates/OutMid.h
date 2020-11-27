#ifndef A380_SYSTEMS_OUTMID_H
#define A380_SYSTEMS_OUTMID_H

#include "Template.h"

namespace PlaneFuelSystem {
    class OutMid: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        OutMid();
        ~OutMid();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };

}


#endif //A380_SYSTEMS_OUTMID_H
