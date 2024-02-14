cmake_minimum_required(VERSION 3.27)
project(TicketsSimulation)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)



add_executable(TicketsSimulation main.cpp
        settings.h
        settings.h)

target_link_libraries(TicketsSimulation nlohmann_json::nlohmann_json)