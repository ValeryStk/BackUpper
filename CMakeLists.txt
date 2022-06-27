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

# tests
enable_testing()
add_subdirectory(Tests)

add_executable       (${projectName} main.cpp)
target_link_libraries(${projectName} PRIVATE CoreLib)
target_link_libraries(${projectName} PRIVATE FileManagerLib)




