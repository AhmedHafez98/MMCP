cmake_minimum_required(VERSION 3.16)

# Set the project name
project(mmcp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable
add_executable(mmcp src/main.cpp)

# If you have additional source files, add them here
# add_executable(MyCppProject src/main.cpp src/another_file.cpp)

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)


# Enable sanitizers
# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#     target_compile_options(mmcp PRIVATE -fsanitize=address,undefined)
#     target_link_options(mmcp PRIVATE -fsanitize=address,undefined)
# endif()

