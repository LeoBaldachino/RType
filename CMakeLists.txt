cmake_minimum_required(VERSION 3.10)

# Add the directory containing FindLibConfig.cmake to the module path
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/libconfig/CMakeLists.txt")

project(r-type_client)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/boost)
# set(BOOST_LIBRARYDIR ${CMAKE_CURRENT_SOURCE_DIR}/boost/stage/lib)
# set(BOOST_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/boost)

# include_directories(${Boost_INCLUDE_DIRS})
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libconfig)


# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 2.6.x)
# FetchContent_MakeAvailable(SFML)
# include_directories(${SFML_SOURCE_DIR}/include)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Visitor)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost)

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

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost)

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

if(WIN32)
    target_link_libraries(r-type_server PRIVATE boost_system boost_serialization Threads::Threads libconfig++)
else()
    target_link_libraries(r-type_server PRIVATE boost_system boost_serialization Threads::Threads config++ config)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(GLOB_RECURSE ASSETS "Assets/*")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Assets PREFIX "Assets" FILES ${ASSETS})

foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONFIG_TYPE})
endforeach()

