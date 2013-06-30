TEMPLATE = lib

SOURCES += \
    sc_kpm_additional.c

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
DESTDIR = ../../sc-machine/bin
OBJECTS_DIR = ./obj

win32 {
    CONFIG += qt console
    LIBS += -L "../../bin" -lsc_memoryd
}

unix {
    LIBS += -L "../../sc-machine/bin" -lsc_memory
}

HEADERS += \
    sc_kpm_additional.h