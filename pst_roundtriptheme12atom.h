#ifndef PST_ROUNDTRIPTHEME12ATOM_H
#define PST_ROUNDTRIPTHEME12ATOM_H

#include "pst_base.h"

class PST_RoundTripTheme12Atom : public PST_Base
{
public:
    PST_RoundTripTheme12Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

#endif // PST_ROUNDTRIPTHEME12ATOM_H
