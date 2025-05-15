cmake_minimum_required(VERSION 3.16)
project(DesktopRadar)

# Use SFML via vcpkg
find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

# Collect all .cpp files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(DesktopRadar ${SOURCES})

# Include custom headers (if needed)
target_include_directories(DesktopRadar PRIVATE include)

# Link SFML (corrected)
target_link_libraries(DesktopRadar PRIVATE SFML::Graphics SFML::Window SFML::System)

# Use C++20
set_property(TARGET DesktopRadar PROPERTY CXX_STANDARD 20)