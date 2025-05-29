cmake_minimum_required(VERSION 3.22)
project(game-of-life CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    )
FetchContent_MakeAvailable(SFML)

include_directories(Inc/)

add_library(Model Src/Model.cpp)

add_library(Game Src/Game.cpp)
target_link_libraries(Game PUBLIC Model)

add_library(SFMLViewController Src/SFMLViewController.cpp)
target_link_libraries(SFMLViewController PUBLIC SFML::Graphics)

add_executable(Main Src/Main.cpp)
target_link_libraries(Main PRIVATE Game SFMLViewController)