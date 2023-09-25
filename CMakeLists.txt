cmake_minimum_required(VERSION 3.10) # You can change this to your minimum required version
project(serverTest)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
add_executable(serverTest ${SERVER_SOURCES} ${SOCKET_SOURCES})

# Link the Boost library
target_link_libraries(serverTest PRIVATE ${Boost_LIBRARIES})

# Link the pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(serverTest PRIVATE Threads::Threads)

# If you have any libraries to link in the future, you can use the following command:
# target_link_libraries(serverTest PRIVATE your_library)
