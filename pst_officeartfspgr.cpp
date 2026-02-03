#include "pst_officeartfspgr.h"

PST_OfficeArtFSPGR::PST_OfficeArtFSPGR(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_OfficeArtFSPGR::parser()
{
	return Error_TODO;
}

void PST_OfficeArtFSPGR::clearParserData()
{
}

int PST_OfficeArtFSPGR::priority()
{
	return 0;
}
