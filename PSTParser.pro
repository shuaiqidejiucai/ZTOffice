QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fopte.cpp \
    main.cpp \
    mainwindow.cpp \
    odraw_officeartbstorecontainer.cpp \
    odraw_officeartsplitmenucolorcontainer.cpp \
    officeartspcontainer.cpp \
    owner.cpp \
    persistdirectoryentry.cpp \
    powerpointbinarydocument.cpp \
    pst_base.cpp \
    pst_binarytagdata.cpp \
    pst_clienttextbox.cpp \
    pst_colorschemeatom.cpp \
    pst_cstring.cpp \
    pst_currentuseratom.cpp \
    pst_document.cpp \
    pst_documentatom.cpp \
    pst_drawingcontainer.cpp \
    pst_drawinggroupcontainer.cpp \
    pst_enddocumentatom.cpp \
    pst_environment.cpp \
    pst_exembed.cpp \
    pst_exobjlist.cpp \
    pst_externalobjectlistatom.cpp \
    pst_externalobjectrefatom.cpp \
    pst_externaloleembedatom.cpp \
    pst_externaloleobjectatom.cpp \
    pst_externaloleobjectstg.cpp \
    pst_externaloleobjectstgatom.cpp \
    pst_fontcollection.cpp \
    pst_groupshapecontainer.cpp \
    pst_handout.cpp \
    pst_headersfooters.cpp \
    pst_list.cpp \
    pst_mainmaster.cpp \
    pst_msofbtbse.cpp \
    pst_msofbtopt.cpp \
    pst_msofbttertiaryopt.cpp \
    pst_normalviewsetinfo.cpp \
    pst_notes.cpp \
    pst_notesatom.cpp \
    pst_notestextviewinfo.cpp \
    pst_oeplaceholderatom.cpp \
    pst_officeartfdg.cpp \
    pst_officeartfsp.cpp \
    pst_officeartfspgr.cpp \
    pst_persistdirectoryatom.cpp \
    pst_ppdrawing.cpp \
    pst_ppdrawinggroup.cpp \
    pst_progbinarytag.cpp \
    pst_progtags.cpp \
    pst_roundtripcolormapping12atom.cpp \
    pst_roundtripcontentmasterid12atom.cpp \
    pst_roundtripcustomtablestyles12.cpp \
    pst_roundtripdocflags12atom.cpp \
    pst_roundtripheaderfooterdefaults12atom.cpp \
    pst_roundtriphfplaceholder12atom.cpp \
    pst_roundtripshapeld12atom.cpp \
    pst_roundtriptheme12atom.cpp \
    pst_shapeclientcontainer.cpp \
    pst_shapecontainer.cpp \
    pst_slide.cpp \
    pst_slideatom.cpp \
    pst_slidelistwithtext.cpp \
    pst_slidenumbermetacharatom.cpp \
    pst_slidepersistatom.cpp \
    pst_slidetime10atom.cpp \
    pst_slideviewinfo.cpp \
    pst_srkinsoku.cpp \
    pst_styletextprop9atom.cpp \
    pst_styletextpropatom.cpp \
    pst_textcharformatexceptionatom.cpp \
    pst_textcharsatom.cpp \
    pst_textheaderatom.cpp \
    pst_textparagraphformatexceptionatom.cpp \
    pst_textruleratom.cpp \
    pst_textspecialinfoatom.cpp \
    pst_textspecialinfodefaultatom.cpp \
    pst_txmasterstyleatom.cpp \
    pst_usereditatom.cpp \
    pst_viewinfoatom.cpp

HEADERS += \
    fopte.h \
    global.h \
    mainwindow.h \
    odraw_officeartbstorecontainer.h \
    odraw_officeartsplitmenucolorcontainer.h \
    officeartspcontainer.h \
    owner.h \
    persistdirectoryentry.h \
    powerpointbinarydocument.h \
    pst_base.h \
    pst_binarytagdata.h \
    pst_clienttextbox.h \
    pst_colorschemeatom.h \
    pst_cstring.h \
    pst_currentuseratom.h \
    pst_document.h \
    pst_documentatom.h \
    pst_drawingcontainer.h \
    pst_drawinggroupcontainer.h \
    pst_enddocumentatom.h \
    pst_environment.h \
    pst_exembed.h \
    pst_exobjlist.h \
    pst_externalobjectlistatom.h \
    pst_externalobjectrefatom.h \
    pst_externaloleembedatom.h \
    pst_externaloleobjectatom.h \
    pst_externaloleobjectstg.h \
    pst_externaloleobjectstgatom.h \
    pst_fontcollection.h \
    pst_groupshapecontainer.h \
    pst_handout.h \
    pst_headersfooters.h \
    pst_list.h \
    pst_mainmaster.h \
    pst_msofbtbse.h \
    pst_msofbtopt.h \
    pst_msofbttertiaryopt.h \
    pst_normalviewsetinfo.h \
    pst_notes.h \
    pst_notesatom.h \
    pst_notestextviewinfo.h \
    pst_oeplaceholderatom.h \
    pst_officeartfdg.h \
    pst_officeartfsp.h \
    pst_officeartfspgr.h \
    pst_persistdirectoryatom.h \
    pst_ppdrawing.h \
    pst_ppdrawinggroup.h \
    pst_progbinarytag.h \
    pst_progtags.h \
    pst_roundtripcolormapping12atom.h \
    pst_roundtripcontentmasterid12atom.h \
    pst_roundtripcustomtablestyles12.h \
    pst_roundtripdocflags12atom.h \
    pst_roundtripheaderfooterdefaults12atom.h \
    pst_roundtriphfplaceholder12atom.h \
    pst_roundtripshapeld12atom.h \
    pst_roundtriptheme12atom.h \
    pst_shapeclientcontainer.h \
    pst_shapecontainer.h \
    pst_slide.h \
    pst_slideatom.h \
    pst_slidelistwithtext.h \
    pst_slidenumbermetacharatom.h \
    pst_slidepersistatom.h \
    pst_slidetime10atom.h \
    pst_slideviewinfo.h \
    pst_srkinsoku.h \
    pst_styletextprop9atom.h \
    pst_styletextpropatom.h \
    pst_textcharformatexceptionatom.h \
    pst_textcharsatom.h \
    pst_textheaderatom.h \
    pst_textparagraphformatexceptionatom.h \
    pst_textruleratom.h \
    pst_textspecialinfoatom.h \
    pst_textspecialinfodefaultatom.h \
    pst_txmasterstyleatom.h \
    pst_usereditatom.h \
    pst_viewinfoatom.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
