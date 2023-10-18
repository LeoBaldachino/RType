cmake_minimum_required(VERSION 3.10)
project(r-type_client)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SUBSYSTEMS "Systems/Subsystems/*.cpp")
file(GLOB SYSTEMS "Systems/*.cpp")
file(GLOB ENTITY "Entity/*.cpp")
file(GLOB CORE "Core/*.cpp")
file(GLOB CLIENT_FILES  "Client/*.cpp")
file(GLOB SOCKET_FILES "Sockets/sources/*.cpp")
file(GLOB ENTITY_TYPES "EntityTypes/*.cpp")
file(GLOB LIFE_BAR "Client/LifeBar/*.cpp")
file(GLOB PARALLAX "Client/Parallax/*.cpp")

add_executable(r-type_client ${CLIENT_FILES} ${SUBSYSTEMS} ${SYSTEMS} ${ENTITY} ${CORE} ${SOCKET_FILES} ${ENTITY_TYPES} ${LIFE_BAR} ${PARALLAX})

target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system sfml-audio pthread)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(r-type_client PRIVATE "-Wno-unused-result")
endif()
