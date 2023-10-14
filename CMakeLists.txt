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

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Leoleo") # Change this to your name
set(CPACK_PACKAGE_DESCRIPTION "R-TYPE SERVER") # Change this to your project description
set(CPACK_PACKAGE_CONTACT "leo.baldachino@epitech.eu") # Change this to your contact information
include(CPack)
