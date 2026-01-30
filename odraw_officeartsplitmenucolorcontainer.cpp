#include "odraw_officeartsplitmenucolorcontainer.h"

ODRAW_OfficeArtSplitMenuColorContainer::ODRAW_OfficeArtSplitMenuColorContainer(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData, var) {}

int ODRAW_OfficeArtSplitMenuColorContainer::parser()
{
    m_isParser = true;
    return Error_BinType;
}

void ODRAW_OfficeArtSplitMenuColorContainer::clearParserData()
{
    m_isParser = false;
}
