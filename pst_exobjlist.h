#ifndef PST_EXOBJLIST_H
#define PST_EXOBJLIST_H

#include "pst_externalobjectlistatom.h"
#include "pst_exembed.h"
class PST_ExObjList : public PST_Base
{
public:
    PST_ExObjList(const QByteArray& srcData);
    virtual int parser();
public:
    QSharedPointer<PST_ExternalObjectListAtom> exObjListAtomPtr;
    QList<QSharedPointer<PST_ExEmbed> > exembedList;
};

#endif // PST_EXOBJLIST_H
