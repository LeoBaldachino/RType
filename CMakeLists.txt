cmake_minimum_required(VERSION 3.10)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Include downloaded libraries via submodule
project(r-type_server)

# Run boost setup
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/boost)
execute_process(COMMAND ${BOOST_ROOT}/bootstrap.sh WORKING_DIRECTORY ${BOOST_ROOT})
execute_process(COMMAND ${BOOST_ROOT}/b2 WORKING_DIRECTORY ${BOOST_ROOT})

# Make sure boost is accessible after running the setup
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${BOOST_ROOT}/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${BOOST_ROOT}/lib")
find_package(Boost)
if (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
endif()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compile flag to "-g"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add your source files
file(GLOB SERVER_SOURCES "server/sources/*.cpp")
file(GLOB SOCKET_SOURCES "Sockets/sources/*.cpp")

# Add your include files
file(GLOB SERVER_INCLUDES "server/includes/*.hpp")
file(GLOB SOCKET_INCLUDES "Sockets/includes/*.hpp")

# Add your executable target
add_executable(r-type_server ${SERVER_SOURCES} ${SOCKET_SOURCES})

# Include cstdint for uintptr_t
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/stacktrace/include)
add_definitions(-D_HAS_AUTO_PTR_ETC=1)
