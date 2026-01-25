#ifndef PST_HEADERSFOOTERS_H
#define PST_HEADERSFOOTERS_H

#include "pst_base.h"

class PST_HeadsFootersAtom : public PST_Base
{
public:
    PST_HeadsFootersAtom(const QByteArray& srcData);
};

class PST_HeadersFooters : public PST_Base
{
public:
    PST_HeadersFooters(const QByteArray& srcData);

    virtual int parser() override;

    QSharedPointer<PST_HeadsFootersAtom> headersFootersAtmo;


};

#endif // PST_HEADERSFOOTERS_H
