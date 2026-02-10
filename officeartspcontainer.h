#ifndef OFFICEARTSPCONTAINER_H
#define OFFICEARTSPCONTAINER_H

#include "pst_base.h"
//F010
class PSTParser_EXPORT OfficeArtSpContainer : public PST_Base
{
public:
    OfficeArtSpContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;

    virtual void clearParserData() override;

    virtual int priority()override;
};

#endif // OFFICEARTSPCONTAINER_H
