cmake_minimum_required(VERSION 4.1)
project(Proiect2POO)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proiect2POO
        main.cpp
        Produs.cpp
        ProdusAlimentar.cpp
        ProdusElectronic.cpp
        ProdusMobilier.cpp
        Cos.cpp
        ProdusFactory.cpp
        ComandaBuilder.cpp
)
