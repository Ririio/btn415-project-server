cmake_minimum_required(VERSION 3.30)
project(btn415_project_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(btn415_project_server main.cpp Thermostat.cpp
        Lights.h
        Lights.cpp
)
