cmake_minimum_required(VERSION 3.13)
project(Aplikacja_tetris)
set(PROJECT_ID apk)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCE_FILES
        src/block.cpp
        src/grid.cpp
        src/game_logic.cpp
)

add_executable(${PROJECT_ID}
        main.cpp
        ${SOURCE_FILES}
)
