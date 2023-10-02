cmake_minimum_required(VERSION 3.10)

project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

file(GLOB SOURCES "sources/*.cpp")

add_executable(server ${SOURCES})

# find_package(SomePackage REQUIRED)
# target_link_libraries(server SomePackage::SomePackage)