#ifndef OFFICEARTCLIENTANCHOR_H
#define OFFICEARTCLIENTANCHOR_H

#include "pst_base.h"

class OfficeArtClientAnchor : public PST_Base
{
public:
    OfficeArtClientAnchor(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
};

#endif // OFFICEARTCLIENTANCHOR_H
