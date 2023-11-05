cmake_minimum_required(VERSION 3.5)

# Add the directory containing FindLibConfig.cmake to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/libconfig/CMakeLists.txt")

project(r-type_client)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# Add the directory to linker library paths
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/asio/asio/include)
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

# Copies the Assets folder to the build directory
add_custom_command(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:r-type_client>/Assets)


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

# CPack configuration for r-type_client
# set(CPACK_PACKAGE_NAME "r-type_client")
# set(CPACK_PACKAGE_VERSION "1.0.0")
# set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/release")
# install(TARGETS r-type_client DESTINATION release)
# include(CPack)

project(r-type_server)
include_directories(${CMAKE_SOURCE_DIR}/external/asio/asio)
include_directories(${CMAKE_SOURCE_DIR}/external/asio/asio/include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


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
    target_link_libraries(r-type_server libconfig++ Threads::Threads)
else()
    target_link_libraries(r-type_server PRIVATE Threads::Threads config++ config)
endif()

# CPack configuration for r-type_server
# set(CPACK_PACKAGE_NAME "r-type_server")
# set(CPACK_PACKAGE_VERSION "1.0.0")
# set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/release")
# add_dependencies(r-type_server config++ config)
# install(TARGETS r-type_server DESTINATION release)
# include(CPack)

project(r-type_room_controller)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB ROOM_SOCKET "Sockets/sources/*.cpp")
file(GLOB ROOM_CONTROLLER "roomController/sources/*.cpp")


add_executable(r-type_room_controller ${ROOM_SOCKET} ${ROOM_CONTROLLER})
target_link_libraries(r-type_room_controller Threads::Threads)

# CPack configuration for r-type_room_controller
# set(CPACK_PACKAGE_NAME "r-type_room_controller")
# set(CPACK_PACKAGE_VERSION "1.0.0")
# set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/release")
# install(TARGETS r-type_room_controller DESTINATION release)
# include(CPack)
