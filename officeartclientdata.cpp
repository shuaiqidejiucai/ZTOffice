#include "officeartclientdata.h"

OfficeArtClientData::OfficeArtClientData(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{}

int OfficeArtClientData::parser()
{
    return 0;
}
