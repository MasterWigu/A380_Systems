//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_OUTINNER_H
#define A380_SYSTEMS_OUTINNER_H

namespace PlaneFuelSystem {
    class OutInner {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        OutInner();
        ~OutInner();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}


#endif //A380_SYSTEMS_OUTINNER_H
