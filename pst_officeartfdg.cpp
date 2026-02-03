#include "pst_officeartfdg.h"

PST_OfficeArtFDG::PST_OfficeArtFDG(const QByteArray &srcData, const ST_Variable& var):PST_Base(srcData,var) {}

int PST_OfficeArtFDG::parser()
{
    return Error_TODO;
}

void PST_OfficeArtFDG::clearParserData()
{
}

int PST_OfficeArtFDG::priority()
{
    return 0;
}
