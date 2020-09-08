//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_INNERFEED23_H
#define A380_SYSTEMS_INNERFEED23_H

namespace PlaneFuelSystem {
    class InnerFeed23 {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        InnerFeed23();
        ~InnerFeed23();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}



#endif //A380_SYSTEMS_INNERFEED23_H
