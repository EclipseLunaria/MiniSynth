cmake_minimum_required(VERSION 3.21)
project(MiniSynth VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(miniSynthSources
    src/main.cpp
)

include(FetchContent)

FetchContent_Declare(
    synthCore
    URL https://github.com/EclipseLunaria/synthCore
)

FetchContent_MakeAvailable(synthCore)

add_executable(main ${miniSynthSources})

target_link_libraries(
    main
    PRIVATE
    synthCore
)