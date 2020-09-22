//
// Created by morei on 03/09/2020.
//

#ifndef A380_SYSTEMS_TEMPLATE_H
#define A380_SYSTEMS_TEMPLATE_H

namespace PlaneFuelSystem {

    class Template {
    public:
        virtual int **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) = 0;
    };
}


#endif //A380_SYSTEMS_TEMPLATE_H
