#include "pst_slideatom.h"

PST_SlideAtom::PST_SlideAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_SlideAtom::parser()
{
	return Error_TODO;
}

void PST_SlideAtom::clearParserData()
{
}

int PST_SlideAtom::priority()
{
	return 0;
}
