cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

project(RentGame)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include(src/sources.cmake)

add_executable(rentGame ${rentGame_SOURCES})
target_link_libraries(rentGame sfml-graphics sfml-window sfml-system)
target_include_directories(rentGame PRIVATE src)
