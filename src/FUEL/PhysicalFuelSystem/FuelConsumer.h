//
// Created by MasterWigu on 29/08/2020.
//

#ifndef UNTITLED_FUELCONSUMER_H
#define UNTITLED_FUELCONSUMER_H

namespace PhysicalFuelSystem {

    /// @class FuelConsumer Represents a valve (normally LP) that supplies fuel to some consumer (engines, APU)
    /// Can be open or closed, and will not work if without power (will stay in the last position)
    /// It works as a "black hole", any fuel that is put into it will "disappear".
    /// It will always try to be fulfilled according to its current consumption rate
    class FuelConsumer {
    private:
        double rate;
        int state; // 0-Closed, 1-Open
        int commandedState;
        double lastSupply;
        bool isPowered;
        bool isJettison;

    public:
        /// Instantiates a Fuel Consumer
        /// @param [in] r - the initial rate the valve is consuming (normally 0)
        /// @param [in] jet - if this consumer is a jettison valve (it will always be fulfilled)
        FuelConsumer(double r, bool jet);

        /// Changes the consumption rate
        /// @param [in] rate - the new consumption rate (in kg/minute)
        void setRate(double rate);

        /// Gets the current state of the valve (open or closed)
        /// @return the state of the valve (0=Closed; 1=Open)
        int getState();

        /// Commands a new state for the valve (only changes the real state if the valve is powered)
        /// @param [in] s - the new commanded state for the valve (0=Closed; 1=Open)
        void setState(int s);

        /// Checks if the valve can consume any fuel (it is open and rate > 0)
        /// @return if it can consume fuel
        bool canConsume();

        /// Tells the valve to consume fuel according to the rate, time period and fuel available
        /// @param [in] amount - the amount of available fuel to consume
        /// @param [in] deltaTime - the time that has passed since last update
        /// @return the fuel that remained (if negative the demand was not fulfilled)
        double consume(double amount, float deltaTime);

        /// Checks if the valve demands were fulfilled in the last consume call
        /// @return if the demands were fulfilled
        bool isFulfilled();


        void setPower(bool p);
        bool getPower();
    };
}


#endif //UNTITLED_FUELCONSUMER_H
