project(FileSystem)

set(SOURCE_FILES
    "FileManager.cpp"
)
set(HEADER_FILES
    "FileManager.h"
    )

add_subdirectory (FileCopier)
add_subdirectory (FileWatcher)
add_subdirectory (FileNameUtil)



add_library(FileManagerLib ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(FileManagerLib PRIVATE FileCopierLib)
target_link_libraries(FileManagerLib PRIVATE FileWatcherLib)


target_include_directories(
FileCopierLib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/FileNameUtil"
)
target_link_libraries(FileCopierLib PRIVATE FileNameUtilLib)
