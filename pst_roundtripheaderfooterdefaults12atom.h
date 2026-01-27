#ifndef PST_ROUNDTRIPHEADERFOOTERDEFAULTS12ATOM_H
#define PST_ROUNDTRIPHEADERFOOTERDEFAULTS12ATOM_H

#include "pst_base.h"

class PST_RoundTripHeaderFooterDefaults12Atom : public PST_Base
{
public:
    PST_RoundTripHeaderFooterDefaults12Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
};

#endif // PST_ROUNDTRIPHEADERFOOTERDEFAULTS12ATOM_H
