#ifndef A380_SYSTEMS_INNERFEED23_H
#define A380_SYSTEMS_INNERFEED23_H

#include "Template.h"

namespace PlaneFuelSystem {
    class InnerFeed23: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        InnerFeed23();
        ~InnerFeed23();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}



#endif //A380_SYSTEMS_INNERFEED23_H
