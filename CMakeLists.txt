cmake_minimum_required(VERSION 3.26)

project(game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXEC main)
set(CMAKE_OSX_ARCHITECTURES arm64)

# Set the location where CMake should look for installed libraries
set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/sfml/2.6.1")

include_directories(includes)

file(GLOB SOURCES src/*.cpp)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(${EXEC} ${SOURCES})

target_link_libraries(${EXEC} sfml-graphics sfml-audio)

add_custom_command(
    TARGET ${EXEC} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/data"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data"
    "${CMAKE_BINARY_DIR}/data"
)
