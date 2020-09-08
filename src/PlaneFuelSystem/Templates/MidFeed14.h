//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_MIDFEED14_H
#define A380_SYSTEMS_MIDFEED14_H

namespace PlaneFuelSystem {
    class MidFeed14 {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        MidFeed14();
        ~MidFeed14();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}



#endif //A380_SYSTEMS_MIDFEED14_H
