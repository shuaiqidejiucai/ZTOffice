#ifndef PERSISTDIRECTORYENTRY_H
#define PERSISTDIRECTORYENTRY_H

#include "pst_base.h"
typedef quint32 PersistOffsetEntry;
class PSTParser_EXPORT PersistDirectoryEntry
{
public:
    PersistDirectoryEntry();

public:
    quint32 persistId;
    quint32 cPersist;
    QList<PersistOffsetEntry> rgPersistOffsetPtr_Array;
};

#endif // PERSISTDIRECTORYENTRY_H
