cmake_minimum_required(VERSION 3.30)
project(Game_of_life_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game_of_life_cpp game_of_life.cpp
        Point.cpp
        Point.h
        World.cpp
        World.h
        Organism.cpp
        Organism.h
        Gameplay.cpp
        Gameplay.h
        Animal.cpp
        Animal.h
        Plant.cpp
        Plant.h)
