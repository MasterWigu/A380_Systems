# cmake_minimum_required(VERSION <specify CMake version here>)
project(A380_Systems)

set(CMAKE_CXX_STANDARD 14)

add_executable(A380_Systems main.cpp FuelSystem/FuelSystem.cpp FuelSystem/FuelSystem.h FuelSystem/FuelTank.cpp FuelSystem/FuelTank.h FuelSystem/FuelPump.cpp FuelSystem/FuelPump.h FuelSystem/FuelTankValve.cpp FuelSystem/FuelTankValve.h FuelSystem/FuelBus.cpp FuelSystem/FuelBus.h FuelSystem/FuelBusValve.cpp FuelSystem/FuelBusValve.h FuelSystem/FuelConsumer.cpp FuelSystem/FuelConsumer.h)