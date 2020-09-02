cmake_minimum_required(VERSION 3.17)
project(A380_Systems)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DIBM -Isrc -m64 -DIBM -DXPLM200 -DXPLM210 -DXPLM300 -DXPLM301 -DXPLM302  -Iinclude/sdk/cheaders/xplm -Iinclude/sdk/cheaders/widgets -shared -Linclude/sdk/libraries/win  -lXPLM_64 -lXPWidgets_64)
add_executable(A380_Systems src/main.cpp src/FuelSystem/FuelSystem.cpp src/FuelSystem/FuelSystem.h src/FuelSystem/FuelTank.cpp src/FuelSystem/FuelTank.h src/FuelSystem/FuelPump.cpp src/FuelSystem/FuelPump.h src/FuelSystem/FuelTankValve.cpp src/FuelSystem/FuelTankValve.h src/FuelSystem/FuelBus.cpp src/FuelSystem/FuelBus.h src/FuelSystem/FuelBusValve.cpp src/FuelSystem/FuelBusValve.h src/FuelSystem/FuelConsumer.cpp src/FuelSystem/FuelConsumer.h src/FuelSystem/EmergTransValve.cpp
        src/PlaneFuelSystem/Tables/Tables.h src/PlaneFuelSystem/Tables/Table0.cpp src/PlaneFuelSystem/Tables/Table1.cpp src/PlaneFuelSystem/Tables/Table2.cpp src/PlaneFuelSystem/Tables/Table3.cpp src/PlaneFuelSystem/DistributionTables.h src/PlaneFuelSystem/DistributionTables.cpp src/PlaneFuelSystem/FuelDistributor.h src/PlaneFuelSystem/FuelDistributor.cpp src/PlaneFuelSystem/FQDC.cpp src/PlaneFuelSystem/FQDC.h src/PlaneFuelSystem/FQMS.cpp src/PlaneFuelSystem/FQMS.h src/PlaneFuelSystem/SystemControl.cpp src/PlaneFuelSystem/SystemControl.h)