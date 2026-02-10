#ifndef PST_ROUNDTRIPHFPLACEHOLDER12ATOM_H
#define PST_ROUNDTRIPHFPLACEHOLDER12ATOM_H

#include "pst_base.h"

class PSTParser_EXPORT PST_RoundTripHFPlaceholder12Atom : public PST_Base
{
public:
    PST_RoundTripHFPlaceholder12Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

#endif // PST_ROUNDTRIPHFPLACEHOLDER12ATOM_H
