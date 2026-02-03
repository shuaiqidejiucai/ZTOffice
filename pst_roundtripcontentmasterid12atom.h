#ifndef PST_ROUNDTRIPCONTENTMASTERID12ATOM_H
#define PST_ROUNDTRIPCONTENTMASTERID12ATOM_H

#include "pst_base.h"

class PST_RoundTripContentMasterId12Atom : public PST_Base
{
public:
    PST_RoundTripContentMasterId12Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

#endif // PST_ROUNDTRIPCONTENTMASTERID12ATOM_H
