#include <cstdlib>
#include "TemplateGetter.h"



namespace PlaneFuelSystem {
    TemplateGetter::TemplateGetter() {

        this->templates = (Template**) malloc(14 * sizeof(Template*));

        this->templates[0] = new InnerFeed14();
        this->templates[1] = new InnerFeed23();
        this->templates[2] = new InnerFeeds();
        this->templates[3] = new InnerOuter();
        this->templates[4] = new MidFeed14();
        this->templates[5] = new MidFeed23();
        this->templates[6] = new MidFeeds();
        this->templates[7] = new MidOuter();
        this->templates[8] = new OutFeeds();
        this->templates[9] = new OutInner();
        this->templates[10] = new OutMid();
        this->templates[11] = new TrimFeeds();
        this->templates[12] = new TrimInner();
        this->templates[13] = new TrimMid();

    }

    int **TemplateGetter::getTemplate(int id, const int *tanks, int *pmpFailures, int *vlvFailures,
                                                       const bool *cases, bool aut, bool someManual) {
        return this->templates[id]->getTemplate(tanks, pmpFailures, vlvFailures, cases, aut, someManual);
    }

}