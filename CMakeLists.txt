cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MySFMLProject VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

file(GLOB SOURCES "*.cpp")

# Create executable
add_executable(doom ${SOURCES})

# Link SFML libraries
target_link_libraries(doom sfml-graphics sfml-window sfml-system)

# Target the current directory for the build process 
target_include_directories(doom PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

