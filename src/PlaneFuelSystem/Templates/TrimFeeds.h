//
// Created by morei on 07/09/2020.
//

#ifndef A380_SYSTEMS_TRIMFEEDS_H
#define A380_SYSTEMS_TRIMFEEDS_H


namespace PlaneFuelSystem {
    class TrimFeeds {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        TrimFeeds();
        ~TrimFeeds();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}

#endif //A380_SYSTEMS_TRIMFEEDS_H
