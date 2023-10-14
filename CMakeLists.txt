cmake_minimum_required(VERSION 3.10)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(SFML)

link_directories(${CMAKE_SOURCE_DIR}/build/SFML/lib)

file(GLOB SFML_LIBS "${CMAKE_SOURCE_DIR}/build/SFML/lib/*.a")
foreach(LIB ${SFML_LIBS})
   link_libraries(${LIB})
endforeach()

set(SOURCE_FILES
main.cpp
Core/Core.cpp
Entity/Player.cpp
Entity/Bydos.cpp
Entity/ShotEntity.cpp
Entity/PiercingShotEntity.cpp
Entity/Tourre.cpp
Systems/PlayerSystem.cpp
Systems/BydosSystem.cpp
Systems/TourreSystem.cpp
Systems/Subsystems/DrawSystem.cpp
Systems/Subsystems/InputSystem.cpp
Systems/Subsystems/PiercingShotSystem.cpp
Systems/Subsystems/ShotSystem.cpp
Systems/Subsystems/MovementSystem.cpp
Systems/Subsystems/AIShoot.cpp
Systems/Subsystems/HitBox.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(r-type_server ${SOURCE_FILES})

target_link_libraries(r-type_server sfml-graphics sfml-window sfml-system sfml-audio)

target_include_directories(r-type_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity
    ${CMAKE_CURRENT_SOURCE_DIR}/Systems
    ${CMAKE_CURRENT_SOURCE_DIR}/Systems/Subsystems
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") # Ignore all compilation warnings

if (UNIX)
    target_link_libraries(r-type_server pthread)
endif (UNIX)

if (WIN32)
    target_link_libraries(r-type_server ws2_32)
endif (WIN32)

