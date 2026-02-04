#ifndef PST_OFFICEARTFDG_H
#define PST_OFFICEARTFDG_H

#include "pst_base.h"

class PST_OfficeArtFDG : public PST_Base
{
public:
    PST_OfficeArtFDG(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_OFFICEARTFDG_H
