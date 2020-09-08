//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_TRIMINNER_H
#define A380_SYSTEMS_TRIMINNER_H

namespace PlaneFuelSystem {
    class TrimInner {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        TrimInner();
        ~TrimInner();

        bool **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut);
    };

}


#endif //A380_SYSTEMS_TRIMINNER_H
