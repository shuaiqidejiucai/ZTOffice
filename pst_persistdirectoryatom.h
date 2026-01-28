#ifndef PST_PERSISTDIRECTORYATOM_H
#define PST_PERSISTDIRECTORYATOM_H

#include "pst_base.h"
#include "persistdirectoryentry.h"
class PST_PersistDirectoryAtom : public PST_Base
{
public:
    PST_PersistDirectoryAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
public:
    QList<QSharedPointer<PersistDirectoryEntry> > rgPersistDirEntryArray;

};

#endif // PST_PERSISTDIRECTORYATOM_H
