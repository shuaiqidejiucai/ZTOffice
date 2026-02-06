#ifndef PST_ROUNDTRIPNOTESMASTERTEXTSTYLES12ATOM_H
#define PST_ROUNDTRIPNOTESMASTERTEXTSTYLES12ATOM_H

#include "pst_base.h"

class PST_RoundTripNotesMasterTextStyles12Atom : public PST_Base
{
public:
    PST_RoundTripNotesMasterTextStyles12Atom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_ROUNDTRIPNOTESMASTERTEXTSTYLES12ATOM_H
