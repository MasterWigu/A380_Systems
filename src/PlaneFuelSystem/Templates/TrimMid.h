//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_TRIMMID_H
#define A380_SYSTEMS_TRIMMID_H

namespace PlaneFuelSystem {
    class TrimMid {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        TrimMid();
        ~TrimMid();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
    };

}


#endif //A380_SYSTEMS_TRIMMID_H
