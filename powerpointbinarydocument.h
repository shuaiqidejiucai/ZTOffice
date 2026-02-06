#ifndef POWERPOINTBINARYDOCUMENT_H
#define POWERPOINTBINARYDOCUMENT_H

#include "global.h"
#include "pst_base.h"

class PSTSearch;
class PST_CurrentUserAtom;
class PST_UserEditAtom;
class PST_PersistDirectoryAtom;
class PST_Document;
class PST_MainMaster;
class PST_Notes;
class PST_Handout;
class PST_Slide;
class PST_ExternaloleObjectStg;
class PowerPointBinaryDocument : public PST_Base
{
public:
    PowerPointBinaryDocument(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData() override;
    virtual int priority()override;
    QSharedPointer<PST_CurrentUserAtom> currentUserAtom;
    QSharedPointer<PST_UserEditAtom> userEditAtomPtr;
    QSharedPointer<PST_PersistDirectoryAtom> persistDirectoryAtomPtr;
    QSharedPointer<PST_Document> documentPtr;
    QList<QSharedPointer<PST_MainMaster> > mainMasterList;
    QList<QSharedPointer<PST_Notes> > notesList;
    QList<QSharedPointer<PST_Handout> > handoutList;
    QList<QSharedPointer<PST_Slide> > slideList;
    QList<QSharedPointer<PST_ExternaloleObjectStg> > exOleObjStringList;

private:
    QHash<quint32, QWeakPointer<PST_Base> > m_HashPtrHash;
};

#endif // POWERPOINTBINARYDOCUMENT_H
