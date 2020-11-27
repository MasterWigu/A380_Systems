#ifndef A380_SYSTEMS_INNEROUTER_H
#define A380_SYSTEMS_INNEROUTER_H

#include "Template.h"

namespace PlaneFuelSystem {
    class InnerOuter: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        InnerOuter();
        ~InnerOuter();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}


#endif //A380_SYSTEMS_INNEROUTER_H
