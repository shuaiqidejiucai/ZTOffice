#ifndef POWERPOINTBINARYDOCUMENT_H
#define POWERPOINTBINARYDOCUMENT_H

#include "global.h"
#include "pst_base.h"
#include "pst_currentuseratom.h"
#include "pst_usereditatom.h"
#include "pst_persistdirectoryatom.h"
#include "pst_document.h"
#include "pst_mainmaster.h"
#include "pst_notes.h"
#include "pst_handout.h"
#include "pst_slide.h"
#include "pst_externaloleobjectstg.h"
class PowerPointBinaryDocument : public PST_Base
{
public:
    PowerPointBinaryDocument(const QByteArray& srcData);

    PST_CurrentUserAtom currentUserAtom;
    PST_UserEditAtom userEditAtom;
    PST_PersistDirectoryAtom persistDirectoryAtom;
    PST_Document document;
    QList<PST_MainMaster> mainMasterList;
    QList<PST_Notes> notesList;
    QList<PST_Slide> slideList;
    QList<PST_ExternaloleObjectStg> exOleObjStringList;
};

#endif // POWERPOINTBINARYDOCUMENT_H
