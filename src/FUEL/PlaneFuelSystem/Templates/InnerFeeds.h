//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_INNERFEEDS_H
#define A380_SYSTEMS_INNERFEEDS_H


#include "Template.h"

namespace PlaneFuelSystem {
    class InnerFeeds: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        InnerFeeds();
        ~InnerFeeds();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}


#endif //A380_SYSTEMS_INNERFEEDS_H
