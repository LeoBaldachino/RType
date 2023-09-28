cmake_minimum_required(VERSION 3.10)
project(r-type)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML COMPONENTS system graphics window REQUIRED) # Find SFML

add_executable(r-type main.cpp Entity/Player.cpp Systems/PlayerSystem.cpp
Systems/Subsystems/DrawSystem.cpp Systems/Subsystems/InputSystem.cpp
Systems/Subsystems/ShotSystem.cpp Entity/ShotEntity.cpp
Systems/Subsystems/PiercingShotSystem.cpp Entity/PiercingShotEntity.cpp
Entity/Bydos.cpp Systems/BydosSystem.cpp Systems/Subsystems/AIShoot.cpp
Systems/Subsystems/MovementSystem.cpp)

target_link_libraries(r-type PRIVATE sfml-system sfml-graphics sfml-window) # Link SFML libraries
set(CMAKE_BUILD_TYPE Debug) # Enable debugging
