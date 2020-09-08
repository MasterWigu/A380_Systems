//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_INNERFEED14_H
#define A380_SYSTEMS_INNERFEED14_H

namespace PlaneFuelSystem {
    class InnerFeed14 {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        InnerFeed14();
        ~InnerFeed14();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}



#endif //A380_SYSTEMS_INNERFEED14_H
