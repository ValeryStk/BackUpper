QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = backup.ico

CONFIG += c++17

SOURCES += \
    CustomButton.cpp \
    DialogCreate.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomButton.h \
    DialogCreate.h \
    mainwindow.h

FORMS += \
    DialogCreate.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

