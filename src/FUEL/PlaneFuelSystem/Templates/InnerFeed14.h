//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_INNERFEED14_H
#define A380_SYSTEMS_INNERFEED14_H

#include "Template.h"

namespace PlaneFuelSystem {
    class InnerFeed14: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        InnerFeed14();
        ~InnerFeed14();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}



#endif //A380_SYSTEMS_INNERFEED14_H
