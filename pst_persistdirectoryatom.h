#ifndef PST_PERSISTDIRECTORYATOM_H
#define PST_PERSISTDIRECTORYATOM_H

#include "global.h"
#include "persistdirectoryentry.h"
class PST_PersistDirectoryAtom
{
public:
    PST_PersistDirectoryAtom(const QByteArray& srcData);


public:
    QList<PersistDirectoryEntry> rgPersistDirEntryArray;
private:
    ST_Variable m_STVar;
    const QByteArray& m_srcData;
};

#endif // PST_PERSISTDIRECTORYATOM_H
