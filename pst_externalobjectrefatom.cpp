#include "pst_externalobjectrefatom.h"

PST_ExternalObjectRefAtom::PST_ExternalObjectRefAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_ExternalObjectRefAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_ExternalObjectRefAtom::clearParserData()
{
}

int PST_ExternalObjectRefAtom::priority()
{
	return 0;
}
