
QT       -= core gui

TARGET = disk_tilestore
TEMPLATE = lib

#CONFIG   += c++0x

SOURCES += \
    plugins/tilestore/disk/disk_tilestore.cpp

HEADERS += \
    plugins/tilestore/disk/disk_tilestore.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += deps include plugins
DEPENDPATH  += deps include plugins

win32 {
    DEFINES += _WINDOWS
    # boost
    INCLUDEPATH += /boost
    DEPENDPATH += /boost
    LIBS += -L/boost/lib32-msvc-10.0
}
