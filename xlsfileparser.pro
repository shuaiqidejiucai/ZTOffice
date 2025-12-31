QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
shareRoot = $$PWD/share
include($$shareRoot/common/common.pri)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    zttools.cpp \
    ztwppdocument.cpp

HEADERS += \
    global.h \
    mainwindow.h \
    zttools.h \
    ztwppdocument.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/qunzip/include
INCLUDEPATH += $$PWD/libolecf/include/common
INCLUDEPATH += $$PWD/libolecf/include/libolecf
INCLUDEPATH += $$PWD/zlib1.3.1Lib/include
win32:msvc* {
    LIBS += -L"$$shareRoot/../zlib1.3.1Lib/lib" -lzlibstaticd
}

LIBS += -L"$$LIBDIR/quazipSelf" -lquazipSelf
LIBS += -L"$$LIBDIR/libolecf" -llibolecf
LIBS += -L"$$LIBDIR/libcdata" -llibcdata
LIBS += -L"$$LIBDIR/libbfio" -llibbfio
LIBS += -L"$$LIBDIR/libcnotify" -llibcnotify
LIBS += -L"$$LIBDIR/libfdatetime" -llibfdatetime
LIBS += -L"$$LIBDIR/libfguid" -llibfguid
LIBS += -L"$$LIBDIR/libfole" -llibfole
LIBS += -L"$$LIBDIR/libfvalue" -llibfvalue
LIBS += -L"$$LIBDIR/libuna" -llibuna
LIBS += -L"$$LIBDIR/libclocale" -llibclocale
LIBS += -L"$$LIBDIR/libcpath" -llibcpath
LIBS += -L"$$LIBDIR/libcfile" -llibcfile
LIBS += -L"$$LIBDIR/libcsplit" -llibcsplit
LIBS += -L"$$LIBDIR/libcerror" -llibcerror

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
