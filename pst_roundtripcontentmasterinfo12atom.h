#ifndef PST_ROUNDTRIPCONTENTMASTERINFO12ATOM_H
#define PST_ROUNDTRIPCONTENTMASTERINFO12ATOM_H

#include "pst_base.h"

class PST_RoundTripContentMasterInfo12Atom : public PST_Base
{
public:
    PST_RoundTripContentMasterInfo12Atom(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_ROUNDTRIPCONTENTMASTERINFO12ATOM_H
