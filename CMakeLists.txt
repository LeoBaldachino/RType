cmake_minimum_required(VERSION 3.5)

# Add the directory containing FindLibConfig.cmake to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/libconfig/CMakeLists.txt")

project(r-type_client)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external/boost)
set(BOOST_LIBRARYDIR ${CMAKE_CURRENT_SOURCE_DIR}/external/boost/stage/lib)
set(BOOST_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/external/boost)
include_directories(${Boost_INCLUDE_DIRS})
# Add the directory to linker library paths
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/boost/stage/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/boost)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/libconfig)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Visitor)

file(GLOB SUBSYSTEMS "ECS/Systems/Subsystems/*.cpp")
file(GLOB SYSTEMS "ECS/Systems/*.cpp")
file(GLOB ENTITY "ECS/Entity/*.cpp")
file(GLOB CORE "Core/*.cpp")
file(GLOB CLIENT_FILES  "Client/*.cpp")
file(GLOB SOCKET_FILES "Sockets/sources/*.cpp")
file(GLOB ENTITY_TYPES "EntityTypes/*.cpp")
file(GLOB LIFE_BAR "Client/LifeBar/*.cpp")
file(GLOB PARALLAX "Client/Parallax/*.cpp")
file(GLOB BUTTON "Client/Button/*.cpp")
file(GLOB MENU "Client/Menu/*.cpp")
file(GLOB POPUP "Client/PopUp/*.cpp")
file(GLOB HUD "Client/Hud/*.cpp")
file(GLOB SOUND_PLAYER "Client/SoundPlayer/*.cpp")
file(GLOB MESSAGE_PANEL "Client/MessagePanel/*.cpp")
add_executable(r-type_client ${CLIENT_FILES} ${SUBSYSTEMS} ${SYSTEMS} ${ENTITY} ${CORE} ${SOCKET_FILES} ${ENTITY_TYPES} ${LIFE_BAR} ${PARALLAX} ${BUTTON} ${MENU} ${POPUP} ${MESSAGE_PANEL} ${HUD} ${SOUND_PLAYER} ${MESSAGE_PANEL})

# target_link_options(r-type_client PRIVATE -g)


find_package(Threads REQUIRED)

if(WIN32)
    target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system sfml-audio Threads::Threads libconfig++)
else()
    target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system sfml-audio Threads::Threads)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(r-type_client PRIVATE "-Wno-unused-result")
endif()

project(r-type_server)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/boost)

file(GLOB SERVER_SOURCES "server/sources/*.cpp")
file(GLOB SERVER_CORE "Core/*.cpp")
file(GLOB SERVER_SOCKET "Sockets/sources/*.cpp")
file(GLOB SERVER_SYSTEMS "ECS/Systems/*.cpp")
file(GLOB SERVER_SUBSYSTEMS "ECS/Systems/Subsystems/*.cpp")
file(GLOB SERVER_ENTITY "ECS/Entity/*.cpp")
file(GLOB SERVER_GAMELOOP "gameLoop/*.cpp")
file(GLOB SERVER_RTYPEGAMELOOP "gameLoop/RTypeGameLoop/*.cpp")
file(GLOB SERVER_ENTITYTYPES "EntityTypes/*.cpp")

add_executable(r-type_server ${SERVER_SOURCES} ${SERVER_CORE} ${SERVER_SOCKET} ${SERVER_SYSTEMS} ${SERVER_SUBSYSTEMS} ${SERVER_ENTITY} ${SERVER_GAMELOOP} ${SERVER_RTYPEGAMELOOP} ${SERVER_ENTITYTYPES})

target_compile_options(r-type_server PRIVATE -g)
target_link_options(r-type_server PRIVATE -g)


# Link against libconfig
if(WIN32)
    target_link_libraries(r-type_server PRIVATE boost_system boost_serialization Threads::Threads libconfig++)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/boost/stage/lib)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/boost)
else()
    target_link_libraries(r-type_server PRIVATE boost_system boost_serialization Threads::Threads config++ config)
endif()

# Copy the Assets folder to the output directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Include the Assets folder in the solution
file(GLOB_RECURSE ASSETS "Assets/*")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Assets PREFIX "Assets" FILES ${ASSETS})

# Copy the Assets folder to the output directory for each configuration
foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONFIG_TYPE})
endforeach()

# Copy the libconfig.dll to the output directory for each configuration
foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/libconfig.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONFIG_TYPE})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/libconfig.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONFIG_TYPE}/libconfig++.dll)
endforeach()

# project(r-type_room_controller)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# file(GLOB ROOM_SOCKET "Sockets/sources/*.cpp")
# file(GLOB ROOM_CONTROLLER "roomController/sources/*.cpp")


# add_executable(r-type_room_controller ${ROOM_SOCKET} ${ROOM_CONTROLLER})
# target_link_libraries(r-type_room_controller PRIVATE boost_system boost_serialization Threads::Threads)
