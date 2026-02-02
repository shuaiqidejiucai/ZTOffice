#ifndef PST_ROUNDTRIPDOCFLAGS12ATOM_H
#define PST_ROUNDTRIPDOCFLAGS12ATOM_H

#include "pst_base.h"

class PST_RoundTripDocFlags12Atom : public PST_Base
{
public:
    PST_RoundTripDocFlags12Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData()override;
};

#endif // PST_ROUNDTRIPDOCFLAGS12ATOM_H
