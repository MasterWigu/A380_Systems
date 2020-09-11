//
// Created by morei on 07/09/2020.
//

#ifndef A380_SYSTEMS_INNEROUTER_H
#define A380_SYSTEMS_INNEROUTER_H

namespace PlaneFuelSystem {
    class InnerOuter {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        InnerOuter();
        ~InnerOuter();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}


#endif //A380_SYSTEMS_INNEROUTER_H
