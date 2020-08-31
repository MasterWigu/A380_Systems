//
// Created by morei on 28/08/2020.
//

#ifndef FUELTANK_H
#define FUELTANK_H
namespace FuelSystem {
    class FuelTank {
    private:
        int capacityKg = -1;
        int currFuelKg = 0;

    public:
        explicit FuelTank(int capacity);
        void setFuel(int fuelKg);
        int getFuel() const;

        int addFuel(int amount);
        int removeFuel(int amount);

        bool isFull() const;
        bool isEmpty() const;
    };
}

#endif //FUELTANK_H
