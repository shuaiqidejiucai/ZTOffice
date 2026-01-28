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
    PowerPointBinaryDocument(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
    QSharedPointer<PST_CurrentUserAtom> currentUserAtom;

    QSharedPointer<PST_UserEditAtom> userEditAtomPtr;
    QSharedPointer<PST_PersistDirectoryAtom> persistDirectoryAtomPtr;
    QSharedPointer<PST_Document> documentPtr;
    QList<QSharedPointer<PST_MainMaster> > mainMasterList;
    QList<QSharedPointer<PST_Notes> > notesList;
    QList<QSharedPointer<PST_Handout> > handoutList;
    QList<QSharedPointer<PST_Slide> > slideList;
    QList<QSharedPointer<PST_ExternaloleObjectStg> > exOleObjStringList;
};

#endif // POWERPOINTBINARYDOCUMENT_H
