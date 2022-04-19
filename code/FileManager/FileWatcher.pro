CONFIG += c++17
CONFIG += console
SOURCES += \
    main.cpp

HEADERS += \
    ArgumentsValidator.h \
    FileCopier.h \
    FileWatcher.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
