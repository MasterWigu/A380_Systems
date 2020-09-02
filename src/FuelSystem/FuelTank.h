//
// Created by morei on 28/08/2020.
//

#ifndef FUELTANK_H
#define FUELTANK_H
namespace FuelSystem {
    class FuelTank {
    private:
        int capacityKg = -1;
        int collectorCapacity;
        int currFuelKg = 0;

    public:
        explicit FuelTank(int capacity);
        FuelTank(int capacity, int collCap);

        void setFuel(int fuelKg);
        int getFuel() const;
        int getCollectorFuel() const;

        int addFuel(int amount);
        int removeFuel(int amount);
        int removeFuelCollector(int amount);

        bool isFull() const;
        bool isEmpty() const;

        bool hasCollector();

        bool isCollectorEmpty() const;
    };
}

#endif //FUELTANK_H
