//
// Created by MasterWigu on 05/09/2020.
//

#ifndef A380_SYSTEMS_MIDFEED14_H
#define A380_SYSTEMS_MIDFEED14_H

#include "Template.h"

namespace PlaneFuelSystem {
    class MidFeed14: public Template {
    private:
        int* valveStates;
        int* pumpStates;
        int ** output;
    public:
        MidFeed14();
        ~MidFeed14();

        int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}



#endif //A380_SYSTEMS_MIDFEED14_H
