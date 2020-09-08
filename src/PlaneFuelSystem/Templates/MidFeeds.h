//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_MIDFEEDS_H
#define A380_SYSTEMS_MIDFEEDS_H

namespace PlaneFuelSystem {
    class MidFeeds {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        MidFeeds();
        ~MidFeeds();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}



#endif //A380_SYSTEMS_MIDFEEDS_H
