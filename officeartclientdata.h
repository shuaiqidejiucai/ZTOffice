#ifndef OFFICEARTCLIENTDATA_H
#define OFFICEARTCLIENTDATA_H

#include "pst_base.h"

class PSTParser_EXPORT OfficeArtClientData : public PST_Base
{
public:
    OfficeArtClientData(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;

    virtual void clearParserData() override;

    virtual int priority()override;
};

#endif // OFFICEARTCLIENTDATA_H
