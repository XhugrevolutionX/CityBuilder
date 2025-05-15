cmake_minimum_required(VERSION 3.31)
project(CityBuilder)

set(CMAKE_CXX_STANDARD 20)

add_executable(CityBuilder main.cpp)

find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

add_subdirectory(game/)

file(COPY ${CMAKE_SOURCE_DIR}/ressources DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(CityBuilder PRIVATE game)