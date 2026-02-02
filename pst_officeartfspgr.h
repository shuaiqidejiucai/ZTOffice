#ifndef PST_OFFICEARTFSPGR_H
#define PST_OFFICEARTFSPGR_H

#include "pst_base.h"

class PST_OfficeArtFSPGR : public PST_Base
{
public:
    PST_OfficeArtFSPGR(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
    virtual void clearParserData()override;
};

#endif // PST_OFFICEARTFSPGR_H
