
project(Core)

set(SOURCE_FILES
    "Controller.cpp"
    )
set(HEADER_FILES
    "Controller.h"
    )
add_subdirectory (Configurator)
add_subdirectory (TimeManager)
add_library(CoreLib ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(CoreLib PRIVATE ConfiguratorLib)
target_link_libraries(CoreLib PRIVATE TimeManagerLib)