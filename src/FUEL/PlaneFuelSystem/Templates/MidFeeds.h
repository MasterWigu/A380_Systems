#ifndef A380_SYSTEMS_MIDFEEDS_H
#define A380_SYSTEMS_MIDFEEDS_H

#include "Template.h"

namespace PlaneFuelSystem {
    class MidFeeds: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        MidFeeds();
        ~MidFeeds();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}

#endif //A380_SYSTEMS_MIDFEEDS_H
