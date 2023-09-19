cmake_minimum_required(VERSION 3.10) # You can change this to your minimum required version
project(server)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source files
file(GLOB SOURCES "server/sources/*.cpp")

# Add your include directories
include_directories(server/includes)
include_directories(Sockets/includes)

# Find the Boost library
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Create the executable
add_executable(server ${SOURCES})

# Link the Boost library
target_link_libraries(server PRIVATE ${Boost_LIBRARIES})

# If you have any libraries to link in the future, you can use the following command:
# target_link_libraries(server PRIVATE your_library)