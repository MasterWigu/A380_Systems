//
// Created by MasterWigu on 28/08/2020.
//

#include "FuelSystem.h"
#include <iostream>

namespace PhysicalFuelSystem {
    FuelSystem::FuelSystem() {
        //TODO express rates in kg/min
        this->tanks = (FuelTank**) malloc(11 * sizeof(FuelTank*));

        this->tanks[0]  = new FuelTank(8117);               //0  - left outer
        this->tanks[1]  = new FuelTank(21691, 1300); //1  - left feed 1
        this->tanks[2]  = new FuelTank(28622);              //2  - left mid
        this->tanks[3]  = new FuelTank(36221);              //3  - left inner
        this->tanks[4]  = new FuelTank(23039, 1300); //4  - left feed 2
        this->tanks[5]  = new FuelTank(23039, 1300); //5  - right feed 3
        this->tanks[6]  = new FuelTank(36221);              //6  - right inner
        this->tanks[7]  = new FuelTank(28622);              //7  - right mid
        this->tanks[8]  = new FuelTank(21691, 1300); //8  - right feed 4
        this->tanks[9]  = new FuelTank(8117);               //9  - right outer
        this->tanks[10] = new FuelTank(18603);              //10 - trim tank


        this->pumps = (FuelPump**) malloc(21 * sizeof(FuelPump*));

        this->pumps[0]  = new FuelPump(this->tanks[1], 15000, true);   //0  - Feed 1 main
        this->pumps[1]  = new FuelPump(this->tanks[1], 15000, true);   //1  - Feed 1 stby
        this->pumps[2]  = new FuelPump(this->tanks[4], 15000, true);   //2  - Feed 2 main
        this->pumps[3]  = new FuelPump(this->tanks[4], 15000, true);   //3  - Feed 2 stby
        this->pumps[4]  = new FuelPump(this->tanks[5], 15000, true);   //4  - Feed 3 main
        this->pumps[5]  = new FuelPump(this->tanks[5], 15000, true);   //5  - Feed 3 stby
        this->pumps[6]  = new FuelPump(this->tanks[8], 15000, true);   //6  - Feed 4 main
        this->pumps[7]  = new FuelPump(this->tanks[8], 15000, true);   //7  - Feed 4 stby
        this->pumps[8]  = new FuelPump(this->tanks[0], 15000, false);  //8  - Left outer pump
        this->pumps[9]  = new FuelPump(this->tanks[2], 15000, false);  //9  - Fwd left mid
        this->pumps[10] = new FuelPump(this->tanks[2], 15000, false);  //10 - Aft left mid
        this->pumps[11] = new FuelPump(this->tanks[3], 15000, false);  //11 - Fwd left inner
        this->pumps[12] = new FuelPump(this->tanks[3], 15000, false);  //12 - Aft left inner
        this->pumps[13] = new FuelPump(this->tanks[6], 15000, false);  //13 - Fwd right inner
        this->pumps[14] = new FuelPump(this->tanks[6], 15000, false);  //14 - Aft right inner
        this->pumps[15] = new FuelPump(this->tanks[7], 15000, false);  //15 - Fwd right mid
        this->pumps[16] = new FuelPump(this->tanks[7], 15000, false);  //16 - Aft right mid
        this->pumps[17] = new FuelPump(this->tanks[9], 15000, false);  //17 - Right outer
        this->pumps[18] = new FuelPump(this->tanks[10], 10000, false); //18 - Trim left
        this->pumps[19] = new FuelPump(this->tanks[10], 10000, false); //19 - Trim right
        this->pumps[20] = new FuelPump(this->tanks[7], 10000, false);  //20 - APU



        this->tankValves = (FuelTankValve**) malloc(22*sizeof(FuelTankValve*));
        this->tankValves[0]  = new FuelTankValve(this->tanks[0], 5000); //0  - Bus0 -> Left Outer
        this->tankValves[1]  = new FuelTankValve(this->tanks[0], 5000); //1  - Bus1 -> Left Outer
        this->tankValves[2]  = new FuelTankValve(this->tanks[1], 0);    //2  - Bus0 -> Left Feed 1
        this->tankValves[3]  = new FuelTankValve(this->tanks[1], 0);    //3  - Bus1 -> Left Feed 1
        this->tankValves[4]  = new FuelTankValve(this->tanks[2], 0);    //4  - Bus0 -> Left Mid
        this->tankValves[5]  = new FuelTankValve(this->tanks[2], 0);    //5  - Bus1 -> Left Mid
        this->tankValves[6]  = new FuelTankValve(this->tanks[3], 0);    //6  - Bus0 -> Left Inner
        this->tankValves[7]  = new FuelTankValve(this->tanks[3], 0);    //7  - Bus1 -> Left Inner
        this->tankValves[8]  = new FuelTankValve(this->tanks[4], 0);    //8  - Bus0 -> Left Feed 2
        this->tankValves[9]  = new FuelTankValve(this->tanks[4], 0);    //9  - Bus1 -> Left Feed 2
        this->tankValves[10] = new FuelTankValve(this->tanks[5], 0);    //10 - Bus0 -> Right Feed 3
        this->tankValves[11] = new FuelTankValve(this->tanks[5], 0);    //11 - Bus1 -> Right Feed 3
        this->tankValves[12] = new FuelTankValve(this->tanks[6], 0);    //12 - Bus0 -> Right Inner
        this->tankValves[13] = new FuelTankValve(this->tanks[6], 0);    //13 - Bus1 -> Right Inner
        this->tankValves[14] = new FuelTankValve(this->tanks[7], 0);    //14 - Bus0 -> Right Mid
        this->tankValves[15] = new FuelTankValve(this->tanks[7], 0);    //15 - Bus1 -> Right Mid
        this->tankValves[16] = new FuelTankValve(this->tanks[8], 0);    //16 - Bus0 -> Right Feed 4
        this->tankValves[17] = new FuelTankValve(this->tanks[8], 0);    //17 - Bus1 -> Right Feed 4
        this->tankValves[18] = new FuelTankValve(this->tanks[9], 5000); //18 - Bus0 -> Right Outer
        this->tankValves[19] = new FuelTankValve(this->tanks[9], 5000); //19 - Bus1 -> Right Outer
        this->tankValves[20] = new FuelTankValve(this->tanks[10], 0);   //20 - Bus7 -> Trim Tank
        this->tankValves[21] = new FuelTankValve(this->tanks[10], 0);   //21 - Bus7 -> Trim Tank


        this->consumers = (FuelConsumer**) malloc(7 * sizeof(FuelConsumer*));

        this->consumers[0] = new FuelConsumer(0, false);     // Eng 1
        this->consumers[1] = new FuelConsumer(0, false);     // Eng 2
        this->consumers[2] = new FuelConsumer(0, false);     // Eng 3
        this->consumers[3] = new FuelConsumer(0, false);     // Eng 4
        this->consumers[4] = new FuelConsumer(0, false);     // APU
        this->consumers[5] = new FuelConsumer(75000, false); // Left Jettison
        this->consumers[6] = new FuelConsumer(75000, false); // Right Jettison
        // NOTE: Jettison consumers have to be always after other consumers, to ensure priority for the engines and APU
        //      to ensure this, jettison consumers have to be after the other AND the bus that has the jettison consumers
        //      has to have a bigger index than the buses that have the engines




        FuelPump* b1Pmps[] = {this->pumps[8], this->pumps[9], this->pumps[11], this->pumps[13], this->pumps[15], this->pumps[17]};  int b1PmpsN = 6;
        FuelPump* b2Pmps[] = {this->pumps[10], this->pumps[12], this->pumps[14], this->pumps[16]};                                  int b2PmpsN = 4;
        FuelPump* b3Pmps[] = {this->pumps[0], this->pumps[1]};                                                                      int b3PmpsN = 2;
        FuelPump* b4Pmps[] = {this->pumps[2], this->pumps[3]};                                                                      int b4PmpsN = 2;
        FuelPump* b5Pmps[] = {this->pumps[4], this->pumps[5]};                                                                      int b5PmpsN = 2;
        FuelPump* b6Pmps[] = {this->pumps[6], this->pumps[7], this->pumps[20]};                                                     int b6PmpsN = 3;
        FuelPump* b7Pmps[] = {nullptr};                                                                                             int b7PmpsN = 0;
        FuelPump* b8Pmps[] = {this->pumps[18], this->pumps[19]};                                                                    int b8PmpsN = 2;


        FuelTankValve* b1tkVls[] = {this->tankValves[0], this->tankValves[2], this->tankValves[4], this->tankValves[6], this->tankValves[8], this->tankValves[10],
                                    this->tankValves[12], this->tankValves[14], this->tankValves[16], this->tankValves[18]};   int b1TkvlN = 10;
        FuelTankValve* b2tkVls[] = {this->tankValves[1], this->tankValves[3], this->tankValves[5], this->tankValves[7], this->tankValves[9], this->tankValves[11],
                                    this->tankValves[13], this->tankValves[15], this->tankValves[17], this->tankValves[19]};   int b2TkvlN = 10;
        FuelTankValve* b3tkVls[] = {nullptr};                                       int b3TkvlN = 0;
        FuelTankValve* b4tkVls[] = {nullptr};                                       int b4TkvlN = 0;
        FuelTankValve* b5tkVls[] = {nullptr};                                       int b5TkvlN = 0;
        FuelTankValve* b6tkVls[] = {nullptr};                                       int b6TkvlN = 0;
        FuelTankValve* b7tkVls[] = {nullptr};                                       int b7TkvlN = 0;
        FuelTankValve* b8tkVls[] = {this->tankValves[18], this->tankValves[19]};    int b8TkvlN = 2;


        FuelConsumer* b1Cons[] = {nullptr};                                     int b1ConsN = 0;
        FuelConsumer* b2Cons[] = {this->consumers[4], this->consumers[5]};      int b2ConsN = 2;
        FuelConsumer* b3Cons[] = {this->consumers[0]};                          int b3ConsN = 1;
        FuelConsumer* b4Cons[] = {this->consumers[1]};                          int b4ConsN = 1;
        FuelConsumer* b5Cons[] = {this->consumers[2]};                          int b5ConsN = 1;
        FuelConsumer* b6Cons[] = {this->consumers[3], this->consumers[4]};      int b6ConsN = 2;
        FuelConsumer* b7Cons[] = {nullptr};                                     int b7ConsN = 0;
        FuelConsumer* b8Cons[] = {nullptr};                                     int b8ConsN = 0;


        this->fuelBuses = (FuelBus**) malloc(8 * sizeof(FuelBus*));

        this->fuelBuses[0] = new FuelBus(0, b1Pmps, b1PmpsN, b1tkVls, b1TkvlN, b1Cons, b1ConsN); //0 - Fwd gallery
        this->fuelBuses[1] = new FuelBus(1, b2Pmps, b2PmpsN, b2tkVls, b2TkvlN, b2Cons, b2ConsN); //1 - Aft gallery
        this->fuelBuses[2] = new FuelBus(2, b3Pmps, b3PmpsN, b3tkVls, b3TkvlN, b3Cons, b3ConsN); //2 - Eng1 feed
        this->fuelBuses[3] = new FuelBus(3, b4Pmps, b4PmpsN, b4tkVls, b4TkvlN, b4Cons, b4ConsN); //3 - Eng2 feed
        this->fuelBuses[4] = new FuelBus(4, b5Pmps, b5PmpsN, b5tkVls, b5TkvlN, b5Cons, b5ConsN); //4 - Eng3 feed
        this->fuelBuses[5] = new FuelBus(5, b6Pmps, b6PmpsN, b6tkVls, b6TkvlN, b6Cons, b6ConsN); //5 - Eng4 feed
        this->fuelBuses[6] = new FuelBus(6, b7Pmps, b7PmpsN, b7tkVls, b7TkvlN, b7Cons, b7ConsN); //6 - Fwd feeds junction
        this->fuelBuses[7] = new FuelBus(7, b8Pmps, b8PmpsN, b8tkVls, b8TkvlN, b8Cons, b8ConsN); //7 - Trim feed


        this->busValves = (FuelBusValve**) malloc(9 * sizeof(FuelBusValve*));

        this->busValves[0] = new FuelBusValve(this->fuelBuses[2], this->fuelBuses[6]); //0 - Eng1 Feed <-> Fwd Feed junction
        this->busValves[1] = new FuelBusValve(this->fuelBuses[3], this->fuelBuses[6]);  //1 - Eng2 Feed <-> Fwd Feed junction
        this->busValves[2] = new FuelBusValve(this->fuelBuses[4], this->fuelBuses[6]);  //2 - Eng3 Feed <-> Fwd Feed junction
        this->busValves[3] = new FuelBusValve(this->fuelBuses[5], this->fuelBuses[6]);  //3 - Eng4 Feed <-> Fwd Feed junction
        this->busValves[4] = new FuelBusValve(this->fuelBuses[6], this->fuelBuses[0]);  //4 - Fwd Feed junction <-> Fwd Gallery
        this->busValves[5] = new FuelBusValve(this->fuelBuses[0], this->fuelBuses[1]);  //5 - Fwd Gallery <-> Aft Gallery
        this->busValves[6] = new FuelBusValve(this->fuelBuses[0], this->fuelBuses[1]);  //6 - Fwd Gallery <-> Aft Gallery
        this->busValves[7] = new FuelBusValve(this->fuelBuses[0], this->fuelBuses[7]);  //7 - Fwd Gallery <-> Trim feed
        this->busValves[8] = new FuelBusValve(this->fuelBuses[1], this->fuelBuses[7]);  //8 - Aft Gallery <-> Trim feed


        FuelBusValve* b1bVls[] = {this->busValves[4], this->busValves[5], this->busValves[6], this->busValves[7]};                      int b1VlsN = 4;
        FuelBusValve* b2bVls[] = {this->busValves[5], this->busValves[6], this->busValves[8]};                                          int b2VlsN = 3;
        FuelBusValve* b3bVls[] = {this->busValves[0]};                                                                                  int b3VlsN = 1;
        FuelBusValve* b4bVls[] = {this->busValves[1]};                                                                                  int b4VlsN = 1;
        FuelBusValve* b5bVls[] = {this->busValves[2]};                                                                                  int b5VlsN = 1;
        FuelBusValve* b6bVls[] = {this->busValves[3]};                                                                                  int b6VlsN = 1;
        FuelBusValve* b7bVls[] = {this->busValves[0], this->busValves[1], this->busValves[2], this->busValves[3], this->busValves[4]};  int b7VlsN = 5;
        FuelBusValve* b8bVls[] = {this->busValves[7], this->busValves[8]};                                                              int b8VlsN = 2;


        this->fuelBuses[0]->setBusValves(b1bVls, b1VlsN);
        this->fuelBuses[1]->setBusValves(b2bVls, b2VlsN);
        this->fuelBuses[2]->setBusValves(b3bVls, b3VlsN);
        this->fuelBuses[3]->setBusValves(b4bVls, b4VlsN);
        this->fuelBuses[4]->setBusValves(b5bVls, b5VlsN);
        this->fuelBuses[5]->setBusValves(b6bVls, b6VlsN);
        this->fuelBuses[6]->setBusValves(b7bVls, b7VlsN);
        this->fuelBuses[7]->setBusValves(b8bVls, b8VlsN);

        this->emergValves = (EmergTansValve**) malloc(2 * sizeof(EmergTansValve*));
        this->emergValves[0] = new EmergTansValve(this->tanks[0], this->tanks[1]); //Left emerg valve
        this->emergValves[1] = new EmergTansValve(this->tanks[9], this->tanks[8]); //Right emerg valve


        this->enginesFulfilled = (bool*) malloc(5 * sizeof(bool));
        for (int i = 0; i < 5; i++) {
            this->enginesFulfilled[i] = true;
        }


        this->electricStatus = (bool*) malloc(8 * sizeof(bool)); //8 electrical buses, 5AC, 3DC
        for (int i = 0; i < 8; i++) {
            this->electricStatus[i] = false; //the plane starts powered down
        }

        this->simTime = -1;
        this->lastSimTime = -1;
    }

    void FuelSystem::printEffectiveNums() {
        for (int i = 0; i < 8; i++) { //we have 8 buses (0-7)
            std::cout << "BUS Num:" << this->fuelBuses[i]->getBusNum() << "  BUS effec num: " << this->fuelBuses[i]->getEfBusNum() << std::endl;
        }
        std::cout << std::endl << std::endl;
    }

    void FuelSystem::debugPrint() {
        std::cout << "TANK FUEL: " << this->tanks[0]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[1]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[2]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[3]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[4]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[5]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[6]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[7]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[8]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[9]->getFuel() << std::endl;
        std::cout << "TANK FUEL: " << this->tanks[10]->getFuel() << std::endl;
        std::cout << std::endl;
    }

    void FuelSystem::testSystem() {
        this->tanks[0]->setFuel(0);  //0  - left outer
        this->tanks[1]->setFuel(10000);  //1  - left feed 1
        this->tanks[2]->setFuel(0);  //2  - left mid
        this->tanks[3]->setFuel(0);  //3  - left inner
        this->tanks[4]->setFuel(10000);  //4  - left feed 2
        this->tanks[5]->setFuel(0);  //5  - right feed 3
        this->tanks[6]->setFuel(0);  //6  - right inner
        this->tanks[7]->setFuel(0);  //7  - right mid
        this->tanks[8]->setFuel(0);  //8  - right feed 4
        this->tanks[9]->setFuel(0);  //9  - right outer
        this->tanks[10]->setFuel(0); //10 - trim tank

        this->pumps[0]->setState(1);  //0  - Feed 1 main
        this->pumps[1]->setState(0);  //1  - Feed 1 stby
        this->pumps[2]->setState(0);  //2  - Feed 2 main
        this->pumps[3]->setState(0);  //3  - Feed 2 stby
        this->pumps[4]->setState(0);  //4  - Feed 3 main
        this->pumps[5]->setState(0);  //5  - Feed 3 stby
        this->pumps[6]->setState(0);  //6  - Feed 4 main
        this->pumps[7]->setState(0);  //7  - Feed 4 stby
        this->pumps[8]->setState(0);  //8  - Left outer pump
        this->pumps[9]->setState(0);  //9  - Fwd left mid
        this->pumps[10]->setState(0); //10 - Aft left mid
        this->pumps[11]->setState(0); //11 - Fwd left inner
        this->pumps[12]->setState(0); //12 - Aft left inner
        this->pumps[13]->setState(0); //13 - Fwd right inner
        this->pumps[14]->setState(0); //14 - Aft right inner
        this->pumps[15]->setState(0); //15 - Fwd right mid
        this->pumps[16]->setState(0); //16 - Aft right mid
        this->pumps[17]->setState(0); //17 - Right outer
        this->pumps[18]->setState(0); //18 - Trim left
        this->pumps[19]->setState(0); //19 - Trim right
        this->pumps[20]->setState(0); //20 - APU

        this->tankValves[0]->setState(0);  //0  - Bus0 -> Left Outer
        this->tankValves[1]->setState(0);  //1  - Bus1 -> Left Outer
        this->tankValves[2]->setState(0);  //2  - Bus0 -> Left Feed 1
        this->tankValves[3]->setState(0);  //3  - Bus1 -> Left Feed 1
        this->tankValves[4]->setState(0);  //4  - Bus0 -> Left Mid
        this->tankValves[5]->setState(0);  //5  - Bus1 -> Left Mid
        this->tankValves[6]->setState(0);  //6  - Bus0 -> Left Inner
        this->tankValves[7]->setState(0);  //7  - Bus1 -> Left Inner
        this->tankValves[8]->setState(0);  //8  - Bus0 -> Left Feed 2
        this->tankValves[9]->setState(0);  //9  - Bus1 -> Left Feed 2
        this->tankValves[10]->setState(0); //10 - Bus0 -> Right Feed 3
        this->tankValves[11]->setState(0); //11 - Bus1 -> Right Feed 3
        this->tankValves[12]->setState(0); //12 - Bus0 -> Right Inner
        this->tankValves[13]->setState(0); //13 - Bus1 -> Right Inner
        this->tankValves[14]->setState(0); //14 - Bus0 -> Right Mid
        this->tankValves[15]->setState(0); //15 - Bus1 -> Right Mid
        this->tankValves[16]->setState(0); //16 - Bus0 -> Right Feed 4
        this->tankValves[17]->setState(0); //17 - Bus1 -> Right Feed 4
        this->tankValves[18]->setState(0); //18 - Bus0 -> Right Outer
        this->tankValves[19]->setState(0); //19 - Bus1 -> Right Outer
        this->tankValves[20]->setState(0); //20 - Bus7 -> Trim Tank
        this->tankValves[21]->setState(0); //21 - Bus7 -> Trim Tank

        this->busValves[0]->setState(0); //0 - Eng1 Feed <-> Fwd Feed junction
        this->busValves[1]->setState(0); //1 - Eng2 Feed <-> Fwd Feed junction
        this->busValves[2]->setState(0); //2 - Eng3 Feed <-> Fwd Feed junction
        this->busValves[3]->setState(0); //3 - Eng4 Feed <-> Fwd Feed junction
        this->busValves[4]->setState(0); //4 - Fwd Feed junction <-> Fwd Gallery
        this->busValves[5]->setState(0); //5 - Fwd Gallery <-> Aft Gallery
        this->busValves[6]->setState(0); //6 - Fwd Gallery <-> Aft Gallery
        this->busValves[7]->setState(0); //7 - Fwd Gallery <-> Trim feed
        this->busValves[8]->setState(1); //8 - Aft Gallery <-> Trim feed


        this->consumers[0]->setState(1);   // Eng 1
        this->consumers[0]->setRate(10);  // Eng 1
        this->consumers[1]->setState(0);   // Eng 2
        this->consumers[1]->setRate(0);  // Eng 2
        this->consumers[2]->setState(1);   // Eng 3
        this->consumers[2]->setRate(10);  // Eng 3
        this->consumers[3]->setState(0);   // Eng 4
        this->consumers[3]->setRate(0);  // Eng 4
        this->consumers[4]->setState(0);   // APU
        this->consumers[4]->setRate(0);  // APU
        this->consumers[5]->setState(0);   // Left   Jettison
        this->consumers[6]->setState(0);   // Right   Jettison
    }

    void FuelSystem::update(float simulatorTime) {

        //calculate time since last update
        if (this->lastSimTime == -1)
            this->lastSimTime = simulatorTime;
        else
            this->lastSimTime = this->simTime;
        this->simTime = simulatorTime;
        float deltaTime = this->simTime - this->lastSimTime;


        //1st stage, reset effective buses
        for (int i = 0; i < 8; i++) { //we have 8 buses (0-7)
            this->fuelBuses[i]->setEfBusNum(i);
        }

        //see fuel readme for explanation of the general algorithm
        //2nd, calculate effective buses
        for (int i = 0; i < 8; i++) { //go through all buses
            FuelBus* currBus = this->fuelBuses[i];


            for (int j = 0; j < currBus->getNumBusValves(); j++) { //iterate over all bus valves in that bus
                FuelBusValve* tempValve = currBus->getBusValves()[j];
                if (tempValve->getState() == 1) { //if valve is open

                    FuelBus* otherBus = tempValve->getLocation1();          //
                    if (otherBus->getBusNum() == currBus->getBusNum()) {    //
                        otherBus = tempValve->getLocation2();               // get the other bus
                    }

                    if (otherBus->getEfBusNum() > currBus->getEfBusNum()) //
                        otherBus->setEfBusNum(currBus->getEfBusNum());    // if the other has bigger index, put our index
                }
            }
        }

        //3rd calculate flows in each effective bus
        double totalAvailBus, totalAvailBusBefDist;


        for (int i = 0; i < 8; i++) { // For each effective bus number
            totalAvailBus = 0;
            for (int j = 0; j < 8; j++) { // We have to get the buses to make calculations
                if (this->fuelBuses[j]->getEfBusNum() == i) { // if the bus has the current effective bus number
                    totalAvailBus += this->fuelBuses[i]->getMaxAvailPumped(deltaTime);
                }
            }
            if (totalAvailBus == 0) { // If all the pumps in the bus are off, check gravity feeds
                for (int j = 0; j < 8; j++) { // We have to get the buses to make calculations
                    if (this->fuelBuses[j]->getEfBusNum() == i) { // if the bus has the current effective bus number
                        totalAvailBus += this->fuelBuses[i]->getMaxAvailGravity(deltaTime);
                    }
                }
            }
            if (totalAvailBus == 0) {
                continue; //if there is no avail fuel in the bus, ignore it
            }

            totalAvailBusBefDist = totalAvailBus;
            for (int j = 0; j < 8; j++) { // distribute the max fuel and see how much remains
                if (this->fuelBuses[j]->getEfBusNum() == i) {
                    totalAvailBus = this->fuelBuses[j]->distribute(totalAvailBus, deltaTime);
                }
            }
            if (totalAvailBus < 0) { //if this happens, we are in trouble for sure
                totalAvailBus = 0; //make it appear as if all was consumed
            }

            for (int j = 0; j < 8; j++) { // pump the fuel we actually used
                if (this->fuelBuses[j]->getEfBusNum() == i) {
                    totalAvailBus = this->fuelBuses[j]->pump(totalAvailBusBefDist - totalAvailBus);
                }
            }
        }

        //if the emergency valves are open, they will transfer fuel
        this->emergValves[0]->transfer(deltaTime);
        this->emergValves[1]->transfer(deltaTime);

        //check if all engines were fulfilled
        for (int i=0; i<5; i++) {
            this->enginesFulfilled[i] = this->consumers[i]->isFulfilled();
        }
    }

    //electricStatus = {0: AC_ESS, 1: AC1, 2: AC2, 3: AC3, 4: AC4, 5: DC_ESS, 6: DC1, 7: DC2}
    void FuelSystem::ACEssChanged(bool powered) {
        this->electricStatus[0] = powered;
        this->pumps[2]->setPower(powered || this->electricStatus[5]); //Feed 2 main pump
        this->pumps[5]->setPower(powered || this->electricStatus[5]); //Feed 3 stby pump
        this->pumps[18]->setPower(powered || this->electricStatus[5]);//Left trim pump
    }

    void FuelSystem::AC1Changed(bool powered) {
        this->electricStatus[1] = powered;
        this->pumps[10]->setPower(powered || this->electricStatus[6]); //Middle aft pump left
        this->pumps[16]->setPower(powered || this->electricStatus[6]); //Middle aft pump right
    }

    void FuelSystem::AC2Changed(bool powered) {
        this->electricStatus[2] = powered;
        this->pumps[1]->setPower(powered); //Feed 1 Stby pump
        this->pumps[6]->setPower(powered); //Feed 4 Main pump
        this->pumps[8]->setPower(powered || this->electricStatus[6]); //Outer left (fwd)
        this->pumps[17]->setPower(powered || this->electricStatus[6]); //Outer right (fwd)
        this->pumps[12]->setPower(powered || this->electricStatus[6]); //Inner left (aft)
        this->pumps[14]->setPower(powered || this->electricStatus[6]); //Inner right (aft)
        this->pumps[19]->setPower(powered || this->electricStatus[6]); //Right trim
    }

    void FuelSystem::AC3Changed(bool powered) {
        this->electricStatus[3] = powered;
        this->pumps[3]->setPower(powered); //Feed 2 Stby pump
        this->pumps[4]->setPower(powered); //Feed 3 Main pump
        this->pumps[9]->setPower(powered || this->electricStatus[7]); //Mid left (fwd)
        this->pumps[15]->setPower(powered || this->electricStatus[7]); //Mid right (fwd)
    }

    void FuelSystem::AC4Changed(bool powered) {
        this->electricStatus[4] = powered;
        this->pumps[0]->setPower(powered); //Feed 1 Main pump
        this->pumps[7]->setPower(powered); //Feed 4 Stby pump
        this->pumps[11]->setPower(powered || this->electricStatus[7]); //Inner left (fwd)
        this->pumps[13]->setPower(powered || this->electricStatus[7]); //Inner right (fwd)
    }

    void FuelSystem::DCEssChanged(bool powered) {
        this->electricStatus[5] = powered;
        this->pumps[2]->setPower(powered || this->electricStatus[0]); //Feed 2 main pump
        this->pumps[5]->setPower(powered || this->electricStatus[0]); //Feed 3 stby pump

        //not sure if all crossfeed valves are supplied by both DC2 and DC_ESS
        this->tankValves[0]->setPower(powered || this->electricStatus[7]);  //Crossfeed
        this->tankValves[1]->setPower(powered || this->electricStatus[7]);  //Crossfeed
        this->tankValves[2]->setPower(powered || this->electricStatus[7]);  //Crossfeed
        this->tankValves[3]->setPower(powered || this->electricStatus[7]);  //Crossfeed

        this->consumers[0]->setPower(powered || this->electricStatus[7]);  //Engine LP valves
        this->consumers[1]->setPower(powered || this->electricStatus[7]);  //Engine LP valves
        this->consumers[2]->setPower(powered || this->electricStatus[7]);  //Engine LP valves
        this->consumers[3]->setPower(powered || this->electricStatus[7]);  //Engine LP valves

        this->pumps[20]->setPower(powered); //APU pump
        this->consumers[3]->setPower(powered);  //APU LP & Isol valves

        this->busValves[5]->setPower(powered); //Left aux refuel valve
        this->tankValves[1]->setPower(powered);  //Outer left aft
        this->tankValves[19]->setPower(powered);  //Outer right aft
        this->pumps[18]->setPower(powered || this->electricStatus[0]); //Trim Left
        this->busValves[8]->setPower(powered); //Trim isolation <-> Aft gallery

        this->emergValves[0]->setPower(powered || this->electricStatus[6]); //Left emerg valve
        this->emergValves[1]->setPower(powered || this->electricStatus[6]); //Left emerg valve
    }

    void FuelSystem::DC1Changed(bool powered) {
        this->electricStatus[6] = powered;
        this->consumers[5]->setPower(powered || this->electricStatus[7]); //Jettison left
        this->consumers[6]->setPower(powered || this->electricStatus[7]); //Jettison right
        this->busValves[4]->setPower(powered); //Transfer/Defuel valve

        this->pumps[8]->setPower(powered || this->electricStatus[2]); //Outer left (fwd)
        this->pumps[17]->setPower(powered || this->electricStatus[2]); //Outer right (fwd)
        this->pumps[10]->setPower(powered || this->electricStatus[1]); //Middle aft pump left
        this->pumps[16]->setPower(powered || this->electricStatus[1]); //Middle aft pump right
        this->pumps[12]->setPower(powered || this->electricStatus[2]); //Inner left (aft)
        this->pumps[14]->setPower(powered || this->electricStatus[2]); //Inner right (aft)
        this->tankValves[20]->setPower(powered); //Trim left valve
        this->pumps[19]->setPower(powered || this->electricStatus[2]); //Right trim
        this->busValves[7]->setPower(powered); //Trim isolation <-> Fwd gallery

        this->emergValves[0]->setPower(powered || this->electricStatus[5]); //Left emerg valve
        this->emergValves[1]->setPower(powered || this->electricStatus[5]); //Left emerg valve
    }

    void FuelSystem::DC2Changed(bool powered) {
        this->electricStatus[7] = powered;
        //not sure if all crossfeed valves are supplied by both DC2 and DC_ESS
        this->tankValves[0]->setPower(powered || this->electricStatus[5]);  //Crossfeed
        this->tankValves[1]->setPower(powered || this->electricStatus[5]);  //Crossfeed
        this->tankValves[2]->setPower(powered || this->electricStatus[5]);  //Crossfeed
        this->tankValves[3]->setPower(powered || this->electricStatus[5]);  //Crossfeed

        this->consumers[0]->setPower(powered || this->electricStatus[5]);  //Engine LP valves
        this->consumers[1]->setPower(powered || this->electricStatus[5]);  //Engine LP valves
        this->consumers[2]->setPower(powered || this->electricStatus[5]);  //Engine LP valves
        this->consumers[3]->setPower(powered || this->electricStatus[5]);  //Engine LP valves

        this->consumers[5]->setPower(powered || this->electricStatus[6]); //Jettison left
        this->consumers[6]->setPower(powered || this->electricStatus[6]); //Jettison right

        this->busValves[6]->setPower(powered); //Right aux refuel valve
        this->tankValves[0]->setPower(powered);  //Outer left fwd
        this->tankValves[18]->setPower(powered);  //Outer right fwd

        this->pumps[9]->setPower(powered || this->electricStatus[3]); //Mid left (fwd)
        this->pumps[15]->setPower(powered || this->electricStatus[3]); //Mid right (fwd)
        this->pumps[11]->setPower(powered || this->electricStatus[4]); //Inner left (fwd)
        this->pumps[13]->setPower(powered || this->electricStatus[4]); //Inner right (fwd)

        this->tankValves[21]->setPower(powered); //Trim right valve
    }

    double FuelSystem::readQuantity(int id) {
        if (id == 11)
            return this->tanks[1]->getCollectorFuel();
        if (id == 12)
            return this->tanks[4]->getCollectorFuel();
        if (id == 13)
            return this->tanks[5]->getCollectorFuel();
        if (id == 14)
            return this->tanks[8]->getCollectorFuel();
        return this->tanks[id]->getFuel();
    }

    int FuelSystem::readValveState(int id) {
        if (id == 28 || id == 29)
            return this->emergValves[id-28]->getState();
        else if (id <= 21)
            return this->tankValves[id]->getState();
        else
            return this->busValves[id-30]->getState();
    }

    void FuelSystem::setValveState(int id, int state) {
        if (id == 28 || id == 29)
            this->emergValves[id-28]->setState(state);
        else if (id <= 21)
            this->tankValves[id]->setState(state);
        else
            this->busValves[id-30]->setState(state);
    }

    int FuelSystem::readPumpState(int id) {
        return this->pumps[id]->getState();
    }

    void FuelSystem::setPumpState(int id, int state) {
        this->pumps[id]->setState(state);
    }



}