cmake_minimum_required(VERSION 3.14)

project(fileWatcher VERSION 0.0.0.1 LANGUAGES CXX)
message ("CMake starts building " ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Threads REQUIRED)
if(UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif (UNIX)

add_executable(FileManager
  main.cpp FileWatcher.h FileCopier.h ArgumentsValidator.h
)

