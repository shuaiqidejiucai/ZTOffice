#include "officeartclientdata.h"

OfficeArtClientData::OfficeArtClientData(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{}

int OfficeArtClientData::parser()
{
    //TODO:事件相关
    return Error_TODO;
}

void OfficeArtClientData::clearParserData()
{
}

int OfficeArtClientData::priority()
{
    return 0;
}
