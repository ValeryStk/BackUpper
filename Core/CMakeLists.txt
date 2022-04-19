
project(Core)

set(SOURCE_FILES
    "Controller.cpp"
    )
set(HEADER_FILES
    "Controller.h"
    )

add_library(CoreLib ${SOURCE_FILES} ${HEADER_FILES})