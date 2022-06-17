cmake_minimum_required(VERSION 3.14)
set(projectName "Ensety")
project(${projectName} VERSION 0.01 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(Core)
add_subdirectory(DataBase)
add_subdirectory(FileSystem)
add_subdirectory(GUI)
add_subdirectory(MessageBroker)
add_subdirectory(Tests)

add_executable (Test Tests/Test.cpp)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_include_directories(
Test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Tests"
)

target_link_libraries(Test PRIVATE gtest_main)
target_link_libraries(Test PRIVATE CoreLib)
target_link_libraries(Test PRIVATE ConfiguratorLib)

add_executable  (${projectName} main.cpp)
target_link_libraries(${projectName} PRIVATE CoreLib)



