cmake_minimum_required(VERSION 3.10)
project(r-type)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML COMPONENTS graphics audio REQUIRED) # Find SFML

add_executable(r-type main.cpp Entity/Player.cpp Systems/PlayerSystem.cpp Systems/Subsystems/DrawSystem.cpp Systems/Subsystems/InputSystem.cpp)

target_link_libraries(r-type PRIVATE sfml-graphics sfml-audio) # Link SFML libraries