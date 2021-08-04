cmake_minimum_required(VERSION 3.20)
project(mastermind)

set(CMAKE_CXX_STANDARD 20)

add_executable(mastermind )
target_sources(mastermind PUBLIC src/main.cpp src/Mastermind.cpp src/Player.cpp src/HumanPlayer.cpp src/CommandLineFunctionality.cpp)
target_include_directories(mastermind PUBLIC include)
target_compile_features(mastermind PUBLIC cxx_std_20)
