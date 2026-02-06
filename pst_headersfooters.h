#ifndef PST_HEADERSFOOTERS_H
#define PST_HEADERSFOOTERS_H

#include "pst_base.h"

class PST_HeadsFootersAtom : public PST_Base
{
public:
    PST_HeadsFootersAtom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

class PST_HeadersFooters : public PST_Base
{
public:
    PST_HeadersFooters(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_HeadsFootersAtom> headersFootersAtom;


};

#endif // PST_HEADERSFOOTERS_H
