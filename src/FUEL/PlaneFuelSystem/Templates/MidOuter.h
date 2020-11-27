#ifndef A380_SYSTEMS_MIDOUTER_H
#define A380_SYSTEMS_MIDOUTER_H

#include "Template.h"

namespace PlaneFuelSystem {
    class MidOuter: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        MidOuter();
        ~MidOuter();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}


#endif //A380_SYSTEMS_MIDOUTER_H
