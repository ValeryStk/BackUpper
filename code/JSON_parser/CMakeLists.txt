cmake_minimum_required(VERSION 3.14)

add_subdirectory(json)
add_subdirectory(tests)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(JsonLib cmake VERSION 0.0.0.1 LANGUAGES CXX)
message ("CMake starts building " ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()



