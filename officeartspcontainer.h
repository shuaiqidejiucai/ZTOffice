#ifndef OFFICEARTSPCONTAINER_H
#define OFFICEARTSPCONTAINER_H

#include "pst_base.h"
//F010
class OfficeArtSpContainer : public PST_Base
{
public:
    OfficeArtSpContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData() override;
};

#endif // OFFICEARTSPCONTAINER_H
