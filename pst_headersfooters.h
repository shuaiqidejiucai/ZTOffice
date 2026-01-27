#ifndef PST_HEADERSFOOTERS_H
#define PST_HEADERSFOOTERS_H

#include "pst_base.h"

class PST_HeadsFootersAtom : public PST_Base
{
public:
    PST_HeadsFootersAtom(const QByteArray& srcData);
    virtual int parser()override;
};

class PST_HeadersFooters : public PST_Base
{
public:
    PST_HeadersFooters(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;

    QSharedPointer<PST_HeadsFootersAtom> headersFootersAtom;


};

#endif // PST_HEADERSFOOTERS_H
