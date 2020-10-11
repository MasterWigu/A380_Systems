//
// Created by morei on 29/08/2020.
//

#ifndef UNTITLED_FUELCONSUMER_H
#define UNTITLED_FUELCONSUMER_H

namespace FuelSystem {
    class FuelConsumer {
    private:
        double rate;
        int state; // 0-Closed, 1-Open
        int commandedState;
        double lastSupply;
        bool isPowered;
        bool isJettison;

    public:
        explicit FuelConsumer(double r);
        FuelConsumer(double r, bool jet);
        void setRate(double rate);

        int getState();
        void setState(int s);

        bool canConsume();
        double consume(double amount, float deltaTime);

        bool isFulfilled();

        void setPower(bool p);
        bool getPower();
    };
}


#endif //UNTITLED_FUELCONSUMER_H
