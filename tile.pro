
QT       -= core gui

TARGET = tile
TEMPLATE = lib

#CONFIG   += c++0x

DEFINES += DATAMAPS_EXPORTS
DEFINES += STATIC_TILESTORE_PLUGINS

SOURCES += \
    src/tile_enumrate.cpp \
    src/tile_pool.cpp \
    src/tile_mix.cpp \
    src/tile_merge.cpp \
    src/tile_io.cpp \
    src/plugin.cpp \
    src/tile_store_box.cpp \
    src/tile_store_box_static.cpp

HEADERS += \
    include/tile/tile.h \
    include/tile/tile_enumrate.h \
    include/tile/tile_store.h \
    include/tile/tile_pool.h \
    include/tile/tile_mix.h \
    include/tile/tile_merge.h \
    include/tile/tile_io.h \
    include/tile/tile_format.h \
    include/tile/tile_store_box.h \
    include/tile/plugin.h \
    include/tile/config.h

#DEFINES += STATIC_TILESTORE_PLUGINS
#SOURCES += plugins/tilestore/disk/disk_tilestore.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    tiles.pro.user

INCLUDEPATH += deps include plugins
DEPENDPATH  += deps include plugins

win32 {
    DEFINES += _WINDOWS
    # boost
    INCLUDEPATH += /boost
    DEPENDPATH += /boost
    LIBS += -L/boost/lib32-msvc-10.0
}
