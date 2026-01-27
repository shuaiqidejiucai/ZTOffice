#ifndef PERSISTDIRECTORYENTRY_H
#define PERSISTDIRECTORYENTRY_H

#include "pst_base.h"
typedef quint32 PersistOffsetEntry;
class PersistDirectoryEntry : public PST_Base
{
public:
    PersistDirectoryEntry(const QByteArray& srcData, const ST_Variable& var);

public:
    quint32 persistId : 20;
    quint32 cPersist : 12;
    QList<QSharedPointer<PersistOffsetEntry> > rgPersistOffsetPtr_Array;
};

#endif // PERSISTDIRECTORYENTRY_H
