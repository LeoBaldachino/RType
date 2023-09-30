cmake_minimum_required(VERSION 3.10) # You can change this to your minimum required version
project(r-type_server)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compile flag to "-g"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add your source files
file(GLOB SERVER_SOURCES "server/sources/*.cpp")
file(GLOB SOCKET_SOURCES "Sockets/sources/*.cpp")

# Add your include directories
include_directories(server/includes)
include_directories(Sockets/includes)

# Find the Boost library
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Create the executable
add_executable(r-type_server ${SERVER_SOURCES} ${SOCKET_SOURCES})

# Link the Boost library
target_link_libraries(r-type_server PRIVATE ${Boost_LIBRARIES})

# Link the pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(r-type_server PRIVATE Threads::Threads)

# If you have any libraries to link in the future, you can use the following command:
# target_link_libraries(r-type_server PRIVATE your_library)
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
