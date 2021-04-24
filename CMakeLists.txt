cmake_minimum_required(VERSION 3.15)
project(BankAccount)

set(CMAKE_CXX_STANDARD 11)

add_executable(BankAccount main.cpp Date.h Date.cpp Accumulator.h Accmulator.cpp Account.h Account.cpp Array.h SelectSort.h)