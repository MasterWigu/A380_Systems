#ifndef FUELTANK_H
#define FUELTANK_H
namespace PhysicalFuelSystem {

    /// @class FuelTank represents each of the fuel tanks
    /// It can have a collector cell with a certain capacity (if it has a collector cell, it will keep it always full until the tank is empty)
    /// It has a maximum capacity and tracks how much fuel it has
    /// It also simulates the flows of fuel according to the configuration of valves and pumps commanded by the plane computers
    class FuelTank {
    private:
        double capacityKg = -1;
        double collectorCapacity;
        double currFuelKg = 0;

    public:
        /// Instantiates a fuel tank with no collector cell
        /// @param [in] capacity - the capacity of the tank in Kg
        explicit FuelTank(double capacity);

        /// Instantiates a fuel tank with or without collector cell
        /// @param [in] capacity - the capacity of the tank in Kg
        /// @param [in] collCap - the capacity of the collector cell (if =0 it means no collector cell)
        FuelTank(double capacity, double collCap);

        /// Sets the amount of fuel in the tank
        /// @param [in] fuelKg - the quantity of fuel in the tank in Kg
        void setFuel(double fuelKg);

        /// Gets the amount of fuel in the tank
        /// @return the quantity of fuel in the tank in Kg
        double getFuel() const;

        /// Gets the amount of fuel in the tank
        /// @return the quantity of fuel in the collector cell in Kg
        double getCollectorFuel() const;

        /// Adds fuel to the tank
        /// @param [in] amount the amount we want to put in the tank
        /// @return the amount of fuel in excess that didn't fit in the tank (overflow)
        double addFuel(double amount);

        /// Removes fuel from the tank
        /// @param [in] amount the amount we want to remove from the tank
        /// @return the amount of fuel we could get from the tank (can be less than asked if the tank became empty)
        double removeFuel(double amount);

        /// Removes fuel from the collector cell
        /// @param [in] amount the amount we want to remove from the tank
        /// @return the amount of fuel we could get from the tank (can be less than asked if the tank became empty)
        double removeFuelCollector(double amount);

        //this is obvious pls
        bool isFull() const;
        bool isEmpty() const;

        bool hasCollector();

        bool isCollectorEmpty() const;
    };
}

#endif //FUELTANK_H
