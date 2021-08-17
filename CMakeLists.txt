cmake_minimum_required(VERSION 3.16)
project(mastermind)

set(CMAKE_CXX_STANDARD 20)


add_executable(mastermind src/Board.cpp include/Board.h)
target_sources(mastermind PUBLIC src/main.cpp src/Game.cpp src/Player.cpp src/HumanPlayer.cpp src/TerminalFunctionality.cpp)
target_include_directories(mastermind PUBLIC include)
target_compile_features(mastermind PUBLIC cxx_std_20)

if (MSVC)
    target_compile_options(mastermind PRIVATE /W4 /WX)
else ()
    target_compile_options(mastermind PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()