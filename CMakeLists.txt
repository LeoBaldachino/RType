cmake_minimum_required(VERSION 3.10) # You can change this to your minimum required version

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compile flag to "-g"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add your source files
file(GLOB SERVER_SOURCES "server/sources/*.cpp")
file(GLOB SOCKET_SOURCES "Sockets/sources/*.cpp")
file(GLOB CORE_SOURCES "Core/*.cpp")
file(GLOB ENTITY_SOURCES "Entity/*.cpp")
file(GLOB SYSTEM_SOURCES "Systems/*.cpp")
file(GLOB SUBSYSTEM_SOURCES "Systems/Subsystems/*.cpp")
file(GLOB GAME_LOOP_SOURCES "gameLoop/*.cpp")
file(GLOB RTYPE_LOOP_SOURCES "gameLoop/RTypeGameLoop/*.cpp")

find_package(SFML COMPONENTS system graphics window REQUIRED)
# Add your include directories
include_directories(server/includes)
include_directories(Sockets/includes)

# Find the Boost library
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Add your executable
add_executable(r-type_server ${SERVER_SOURCES} ${SOCKET_SOURCES})