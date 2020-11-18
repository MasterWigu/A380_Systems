//
// Created by MasterWigu on 07/09/2020.
//

#ifndef A380_SYSTEMS_TRIMFEEDS_H
#define A380_SYSTEMS_TRIMFEEDS_H


#include "Template.h"

namespace PlaneFuelSystem {
    class TrimFeeds: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        TrimFeeds();
        ~TrimFeeds();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}

#endif //A380_SYSTEMS_TRIMFEEDS_H
