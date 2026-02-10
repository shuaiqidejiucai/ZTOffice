#ifndef PST_ROUNDTRIPCUSTOMTABLESTYLES12_H
#define PST_ROUNDTRIPCUSTOMTABLESTYLES12_H

#include "pst_base.h"

class PSTParser_EXPORT PST_RoundTripCustomTableStyles12 : public PST_Base
{
public:
    PST_RoundTripCustomTableStyles12(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_ROUNDTRIPCUSTOMTABLESTYLES12_H
