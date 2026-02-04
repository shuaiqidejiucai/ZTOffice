#ifndef PSTSEARCH_H
#define PSTSEARCH_H
#include "pst_base.h"
class PSTSearch
{
public:
    PSTSearch();

    bool insertRecordMap(quint32 key, const QWeakPointer<PST_Base> & value);
private:
    QMap<quint32, QWeakPointer<PST_Base> > m_posVPSTBaseMap;
};

#endif // PSTSEARCH_H
