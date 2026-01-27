#ifndef PST_EXOBJLIST_H
#define PST_EXOBJLIST_H

#include "pst_externalobjectlistatom.h"
#include "pst_exembed.h"
class PST_ExObjList : public PST_Base
{
public:
    PST_ExObjList(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser() override;
public:
    QSharedPointer<PST_ExternalObjectListAtom> exObjListAtomPtr;
    QList<QSharedPointer<PST_ExEmbed> > exembedList;
    //TODO:其他类型的数据
};

#endif // PST_EXOBJLIST_H
