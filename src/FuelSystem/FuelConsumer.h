//
// Created by morei on 29/08/2020.
//

#ifndef UNTITLED_FUELCONSUMER_H
#define UNTITLED_FUELCONSUMER_H

namespace FuelSystem {
    class FuelConsumer {
    private:
        int rate;
        int state; // 0-Closed, 1-Open
        int lastSupply;
        bool isJettison;

    public:
        explicit FuelConsumer(int r);
        FuelConsumer(int r, bool jet);
        void setRate(int rate);

        int getState();
        void setState(int s);

        bool canConsume();
        int consume(int amount);

        bool isFulfilled();
    };
}


#endif //UNTITLED_FUELCONSUMER_H
