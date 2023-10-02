cmake_minimum_required(VERSION 3.10) # You can change this to your minimum required version

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compile flag to "-g"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Server build
project(r-type_server)

# Add your source files
file(GLOB SERVER_SOURCES "server/sources/*.cpp")
file(GLOB SOCKET_SOURCES "Sockets/sources/*.cpp")

# Add your include directories
include_directories(server/includes)
include_directories(Sockets/includes)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/boost)
set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories(${Boost_LIBRARY_DIR})

# Set the output directory for the build executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/server)

# Add your executable
add_executable(r-type_server ${SERVER_SOURCES} ${SOCKET_SOURCES})

# Link your executable against the libraries
target_link_libraries(r-type_server ${Boost_LIBRARIES})

# Client build
project(r-type_client)

file(GLOB CLIENT_SOURCES "main.cpp" "Core/Core.cpp" "Entity/Player.cpp" "Entity/Bydos.cpp" "Entity/ShotEntity.cpp" "Entity/PiercingShotEntity.cpp" "Systems/PlayerSystem.cpp" "Systems/BydosSystem.cpp" "Systems/Subsystems/DrawSystem.cpp" "Systems/Subsystems/InputSystem.cpp" "Systems/Subsystems/PiercingShotSystem.cpp" "Systems/Subsystems/ShotSystem.cpp" "Systems/Subsystems/MovementSystem.cpp" "Systems/Subsystems/AIShoot.cpp")

# Find SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML")
if(NOT EXISTS "${SFML_DIR}")
  execute_process(COMMAND git submodule update --init SFML
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Set the output directory for the build executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/client)

# Copy Assets to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Add your executable
add_executable(r-type_client ${CLIENT_SOURCES})

# Link your executable against the libraries
target_link_libraries(r-type_client ${Boost_LIBRARIES} sfml-graphics sfml-audio)



