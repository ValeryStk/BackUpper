project(FileCopier)

set(SOURCE_FILES
    "FileCopier.cpp"
)
set(HEADER_FILES
    "FileCopier.h"
    )

add_library(FileCopierLib ${SOURCE_FILES} ${HEADER_FILES})
