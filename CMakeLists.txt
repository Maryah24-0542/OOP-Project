cmake_minimum_required(VERSION 3.20)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_Project
        main.cpp
        Company.cpp
        order.cpp
        customer.cpp
        Restaurant.cpp
        Menu.cpp
        Driver.cpp
        BikeDriver.cpp
        CarDriver.cpp
        Payment.cpp
        CashPayment.cpp
        CardPayment.cpp
)