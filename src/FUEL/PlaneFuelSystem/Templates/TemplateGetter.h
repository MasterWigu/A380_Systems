//
// Created by MasterWigu on 03/09/2020.
//

#ifndef A380_SYSTEMS_TEMPLATEGETTER_H
#define A380_SYSTEMS_TEMPLATEGETTER_H

#include "Template.h"
#include "InnerFeed14.h"
#include "InnerFeed23.h"
#include "InnerFeeds.h"
#include "InnerOuter.h"
#include "MidFeed14.h"
#include "MidFeed23.h"
#include "MidFeeds.h"
#include "MidOuter.h"
#include "OutFeeds.h"
#include "OutInner.h"
#include "OutMid.h"
#include "TrimFeeds.h"
#include "TrimInner.h"
#include "TrimMid.h"

namespace PlaneFuelSystem {
    class TemplateGetter {
    private:
        PlaneFuelSystem::Template** templates;

    public:
        TemplateGetter();

        int** getTemplate(int id, const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);

    };

}


#endif //A380_SYSTEMS_TEMPLATEGETTER_H
