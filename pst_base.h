#ifndef PST_BASE_H
#define PST_BASE_H
#include "global.h"
class PST_Base
{
public:
    PST_Base(const QByteArray& srcData);

protected:
    ST_Variable m_STVar;
    const QByteArray& m_srcData;
};

#endif // PST_BASE_H
