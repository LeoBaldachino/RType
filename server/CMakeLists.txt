cmake_minimum_required(VERSION 3.10)

project(r-type_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

file(GLOB SOURCES "sources/*.cpp")
file(GLOB CORE "../Core/*.cpp")
file(GLOB SOCKET "../Sockets/sources/*.cpp")
file(GLOB SYSTEMS "../Systems/*.cpp")
file(GLOB SUBSYSTEMS "../Systems/Subsystems/*.cpp")
file(GLOB ENTITY "../Entity/*.cpp")
file(GLOB GAMELOOP "../gameLoop/*.cpp")
file(GLOB RTYPEGAMELOOP "../gameLoop/RTypeGameLoop/*.cpp")

set(SFML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../SFML)
if(NOT EXISTS "${SFML_ROOT}")
    # SFML not found. Download and install it.
    message(STATUS "SFML not found. Downloading...")
    execute_process(COMMAND git submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
link_directories(${SFML_LIBRARY_DIR})

add_executable(r-type_server ${SOURCES} ${CORE} ${SOCKET} ${SYSTEMS} ${SUBSYSTEMS} ${ENTITY} ${GAMELOOP} ${RTYPEGAMELOOP})
target_include_directories(r-type_server PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(r-type_server sfml-system sfml-graphics sfml-window)
target_link_libraries(r-type_server pthread)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD_REQUIRED ON)


# find_package(SomePackage REQUIRED)
# target_link_libraries(server SomePackage::SomePackage)