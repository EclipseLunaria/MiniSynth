cmake_minimum_required(VERSION 3.21)
project(MiniSynth VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(miniSynthSources
    src/main.cpp
    src/window.cpp
)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_subdirectory(deps/synthCore)

add_executable(main ${miniSynthSources})

target_include_directories(main PUBLIC include)

target_link_libraries(
    main
    PRIVATE
    synthCore
    SDL3::SDL3-shared
)