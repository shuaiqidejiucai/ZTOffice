QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    persistdirectoryentry.cpp \
    powerpointbinarydocument.cpp \
    pst_base.cpp \
    pst_cstring.cpp \
    pst_currentuseratom.cpp \
    pst_document.cpp \
    pst_documentatom.cpp \
    pst_environment.cpp \
    pst_exembed.cpp \
    pst_exobjlist.cpp \
    pst_externalobjectlistatom.cpp \
    pst_externaloleembedatom.cpp \
    pst_externaloleobjectatom.cpp \
    pst_externaloleobjectstgatom.cpp \
    pst_fontcollection.cpp \
    pst_handout.cpp \
    pst_mainmaster.cpp \
    pst_notes.cpp \
    pst_persistdirectoryatom.cpp \
    pst_ppdrawinggroup.cpp \
    pst_slide.cpp \
    pst_srkinsoku.cpp \
    pst_textcharformatexceptionatom.cpp \
    pst_textparagraphformatexceptionatom.cpp \
    pst_textspecialinfodefaultatom.cpp \
    pst_txmasterstyleatom.cpp

HEADERS += \
    global.h \
    mainwindow.h \
    persistdirectoryentry.h \
    powerpointbinarydocument.h \
    pst_base.h \
    pst_cstring.h \
    pst_currentuseratom.h \
    pst_document.h \
    pst_documentatom.h \
    pst_environment.h \
    pst_exembed.h \
    pst_exobjlist.h \
    pst_externalobjectlistatom.h \
    pst_externaloleembedatom.h \
    pst_externaloleobjectatom.h \
    pst_externaloleobjectstgatom.h \
    pst_fontcollection.h \
    pst_handout.h \
    pst_mainmaster.h \
    pst_notes.h \
    pst_persistdirectoryatom.h \
    pst_ppdrawinggroup.h \
    pst_slide.h \
    pst_srkinsoku.h \
    pst_textcharformatexceptionatom.h \
    pst_textparagraphformatexceptionatom.h \
    pst_textspecialinfodefaultatom.h \
    pst_txmasterstyleatom.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
