#ifndef A380_SYSTEMS_MIDFEED23_H
#define A380_SYSTEMS_MIDFEED23_H

#include "Template.h"

namespace PlaneFuelSystem {
    class MidFeed23: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        MidFeed23();
        ~MidFeed23();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}



#endif //A380_SYSTEMS_MIDFEED23_H
