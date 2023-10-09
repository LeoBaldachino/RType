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
#project(r-type_server)

# Run boost setup
#set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/boost)
#execute_process(COMMAND ${BOOST_ROOT}/bootstrap.sh WORKING_DIRECTORY ${BOOST_ROOT})
#execute_process(COMMAND ${BOOST_ROOT}/b2 WORKING_DIRECTORY ${BOOST_ROOT})

# Make sure boost is accessible after running the setup
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${BOOST_ROOT}/include")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${BOOST_ROOT}/lib")
#find_package(Boost)
#if (Boost_FOUND)
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#    ADD_DEFINITIONS( "-DHAS_BOOST" )
#endif()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compile flag to "-g"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add your source files
#file(GLOB SERVER_SOURCES "server/sources/*.cpp")
#file(GLOB SOCKET_SOURCES "Sockets/sources/*.cpp")

# Add your include files
#file(GLOB SERVER_INCLUDES "server/includes/*.hpp")
#file(GLOB SOCKET_INCLUDES "Sockets/includes/*.hpp")

# Add your executable target
#add_executable(r-type_server ${SERVER_SOURCES} ${SOCKET_SOURCES})

# Include cstdint for uintptr_t
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/stacktrace/include)
#add_definitions(-D_HAS_AUTO_PTR_ETC=1)

# Build client
project(r-type_client)

# Add your source files
set(SFML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/SFML)
if(GIT_SUBMODULE)
    message(STATUS "SFML submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${SFML_ROOT}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")
link_directories(${SFML_LIBRARY_DIR})

set(CLIENT_SOURCES main.cpp Core/Core.cpp Entity/Player.cpp Entity/Bydos.cpp Entity/ShotEntity.cpp Entity/PiercingShotEntity.cpp Systems/PlayerSystem.cpp Systems/BydosSystem.cpp Systems/Subsystems/DrawSystem.cpp Systems/Subsystems/InputSystem.cpp Systems/Subsystems/PiercingShotSystem.cpp Systems/Subsystems/ShotSystem.cpp Systems/Subsystems/MovementSystem.cpp Systems/Subsystems/AIShoot.cpp)
add_executable(r-type_client ${CLIENT_SOURCES})
target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(r-type_client sfml-system sfml-graphics sfml-window)

# Specify the C++ standard
set_property(TARGET r-type_client PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED ON)

