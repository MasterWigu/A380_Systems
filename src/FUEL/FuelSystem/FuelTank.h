//
// Created by morei on 28/08/2020.
//

#ifndef FUELTANK_H
#define FUELTANK_H
namespace FuelSystem {
    class FuelTank {
    private:
        double capacityKg = -1;
        double collectorCapacity;
        double currFuelKg = 0;

    public:
        explicit FuelTank(double capacity);
        FuelTank(double capacity, double collCap);

        void setFuel(double fuelKg);
        double getFuel() const;
        double getCollectorFuel() const;

        double addFuel(double amount);
        double removeFuel(double amount);
        double removeFuelCollector(double amount);

        bool isFull() const;
        bool isEmpty() const;

        bool hasCollector();

        bool isCollectorEmpty() const;
    };
}

#endif //FUELTANK_H
