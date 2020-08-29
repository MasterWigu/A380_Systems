//
// Created by morei on 28/08/2020.
//

#include "FuelSystem.h"



namespace FuelSystem {
    FuelSystem::FuelSystem() {
        FuelTank tks[11] = {FuelTank(8117),    //0  - left outer
                             FuelTank(21691),  //1  - left feed 1
                             FuelTank(28622),  //2  - left mid
                             FuelTank(36221),  //3  - left inner
                             FuelTank(23039),  //4  - left feed 2
                             FuelTank(23039),  //5  - right feed 3
                             FuelTank(36221),  //6  - right inner
                             FuelTank(28622),  //7  - right mid
                             FuelTank(21691),  //8  - right feed 4
                             FuelTank(8117),   //9  - right outer
                             FuelTank(18603)}; //10 - trim tank

        FuelPump pps[21] = {FuelPump(&tks[1], 15000), //0  - Feed 1 main
                            FuelPump(&tks[1], 15000), //1  - Feed 1 stby
                            FuelPump(&tks[4], 15000), //2  - Feed 2 main
                            FuelPump(&tks[4], 15000), //3  - Feed 2 stby
                            FuelPump(&tks[5], 15000), //4  - Feed 3 main
                            FuelPump(&tks[5], 15000), //5  - Feed 3 stby
                            FuelPump(&tks[8], 15000), //6  - Feed 4 main
                            FuelPump(&tks[8], 15000), //7  - Feed 4 stby
                            FuelPump(&tks[0], 15000), //8  - Left outer pump
                            FuelPump(&tks[2], 15000), //9  - Fwd left mid
                            FuelPump(&tks[2], 15000), //10 - Aft left mid
                            FuelPump(&tks[3], 15000), //11 - Fwd left inner
                            FuelPump(&tks[3], 15000), //12 - Aft left inner
                            FuelPump(&tks[6], 15000), //13 - Fwd right inner
                            FuelPump(&tks[6], 15000), //14 - Aft right inner
                            FuelPump(&tks[7], 15000), //15 - Fwd right mid
                            FuelPump(&tks[7], 15000), //16 - Aft right mid
                            FuelPump(&tks[9], 15000), //17 - Right outer
                            FuelPump(&tks[10], 10000), //18 - Trim left
                            FuelPump(&tks[10], 10000), //19 - Trim right
                            FuelPump(&tks[7], 10000), //20 - APU
                            };

        // TODO try to guess gravity feed rates
        FuelTankValve tksVls[22] = {FuelTankValve(&tks[0], 5000), //Bus1 -> Left Outer
                                    FuelTankValve(&tks[0], 5000), //Bus2 -> Left Outer
                                    FuelTankValve(&tks[1], 0), //Bus1 -> Left Feed 1
                                    FuelTankValve(&tks[1], 0), //Bus1 -> Left Feed 1
                                    FuelTankValve(&tks[2], 0), //Bus1 -> Left Mid
                                    FuelTankValve(&tks[2], 0), //Bus2 -> Left Mid
                                    FuelTankValve(&tks[3], 0), //Bus1 -> Left Inner
                                    FuelTankValve(&tks[3], 0), //Bus2 -> Left Inner
                                    FuelTankValve(&tks[4], 0), //Bus1 -> Left Feed 2
                                    FuelTankValve(&tks[4], 0), //Bus2 -> Left Feed 2
                                    FuelTankValve(&tks[5], 0), //Bus1 -> Right Feed 3
                                    FuelTankValve(&tks[5], 0), //Bus2 -> Right Feed 3
                                    FuelTankValve(&tks[6], 0), //Bus1 -> Right Inner
                                    FuelTankValve(&tks[6], 0), //Bus2 -> Right Inner
                                    FuelTankValve(&tks[7], 0), //Bus1 -> Right Mid
                                    FuelTankValve(&tks[7], 0), //Bus2 -> Right Mid
                                    FuelTankValve(&tks[8], 0), //Bus1 -> Right Feed 4
                                    FuelTankValve(&tks[8], 0), //Bus2 -> Right Feed 4
                                    FuelTankValve(&tks[9], 5000), //Bus1 -> Right Outer
                                    FuelTankValve(&tks[9], 5000), //Bus2 -> Right Outer
                                    FuelTankValve(&tks[10], 0), //BusT -> Trim Tank
                                    FuelTankValve(&tks[10], 0), //BusT -> Trim Tank
                                    };


        FuelConsumer consumers[7] = {FuelConsumer(0, false), // Eng 1
                                     FuelConsumer(0, false), // Eng 2
                                     FuelConsumer(0, false), // Eng 3
                                     FuelConsumer(0, false), // Eng 4
                                     FuelConsumer(0, false), // APU
                                     FuelConsumer(75000, false), // Left Jettison
                                     FuelConsumer(75000, false), // Right Jettison
                                     };

        //FuelPump b1Pmps[6]


        //FuelBus buses[8] = {FuelBus

        //};




    }

}