#ifndef PST_ROUNDTRIPCUSTOMTABLESTYLES12_H
#define PST_ROUNDTRIPCUSTOMTABLESTYLES12_H

#include "pst_base.h"

class PST_RoundTripCustomTableStyles12 : public PST_Base
{
public:
    PST_RoundTripCustomTableStyles12(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;
};

#endif // PST_ROUNDTRIPCUSTOMTABLESTYLES12_H
