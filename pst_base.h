#ifndef PST_BASE_H
#define PST_BASE_H
#include "global.h"
#include "zttools.h"
class PST_Base
{
public:
    PST_Base(const QByteArray& srcData, const ST_Variable& var);

    int parserData();

    void clearData();
protected:
    virtual int parser() = 0;

    virtual void clearParserData() = 0;
protected:
    const ST_Variable m_STVar;
    const QByteArray& m_srcData;
    bool m_isParser;
};

#endif // PST_BASE_H
