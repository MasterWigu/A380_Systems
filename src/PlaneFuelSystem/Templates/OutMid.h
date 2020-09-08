//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_OUTMID_H
#define A380_SYSTEMS_OUTMID_H

namespace PlaneFuelSystem {
    class OutMid {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        OutMid();
        ~OutMid();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
    };

}


#endif //A380_SYSTEMS_OUTMID_H
