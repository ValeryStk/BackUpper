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

add_executable (TestIntegration Tests/Test.cpp)
add_executable (TestCopy Tests/FileCopierTest.cpp)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_include_directories(
TestIntegration PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Tests"
)
target_include_directories(
TestCopy PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Tests"
)

target_link_libraries(TestIntegration PRIVATE gtest_main)
target_link_libraries(TestIntegration PRIVATE CoreLib)
target_link_libraries(TestIntegration PRIVATE ConfiguratorLib)
target_link_libraries(TestIntegration PRIVATE FileManagerLib)

target_link_libraries(TestCopy PRIVATE gtest_main)
target_link_libraries(TestCopy PRIVATE FileManagerLib)

add_executable       (${projectName} main.cpp)
target_link_libraries(${projectName} PRIVATE CoreLib)
target_link_libraries(${projectName} PRIVATE FileManagerLib)




