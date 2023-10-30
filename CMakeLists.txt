cmake_minimum_required(VERSION 3.10)

# Add the directory containing FindLibConfig.cmake to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

project(r-type_client)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_SOURCE_DIR}/include)

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

find_package(Threads REQUIRED)
target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system sfml-audio Threads::Threads)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(r-type_client PRIVATE "-Wno-unused-result")
endif()

project(r-type_server)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/boost)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libconfig)

file(GLOB SERVER_SOURCES "server/sources/*.cpp")
file(GLOB SERVER_CORE "Core/*.cpp")
file(GLOB SERVER_SOCKET "Sockets/sources/*.cpp")
file(GLOB SERVER_SYSTEMS "Systems/*.cpp")
file(GLOB SERVER_SUBSYSTEMS "Systems/Subsystems/*.cpp")
file(GLOB SERVER_ENTITY "Entity/*.cpp")
file(GLOB SERVER_GAMELOOP "gameLoop/*.cpp")
file(GLOB SERVER_RTYPEGAMELOOP "gameLoop/RTypeGameLoop/*.cpp")
file(GLOB SERVER_ENTITYTYPES "EntityTypes/*.cpp")

add_executable(r-type_server ${SERVER_SOURCES} ${SERVER_CORE} ${SERVER_SOCKET} ${SERVER_SYSTEMS} ${SERVER_SUBSYSTEMS} ${SERVER_ENTITY} ${SERVER_GAMELOOP} ${SERVER_RTYPEGAMELOOP} ${SERVER_ENTITYTYPES})

# Link against libconfig
target_link_libraries(r-type_server PRIVATE boost_system boost_serialization Threads::Threads config++)
