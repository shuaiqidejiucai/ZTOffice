#include "pst_textheaderatom.h"

PST_TextHeaderAtom::PST_TextHeaderAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var),textType(0) {}

int PST_TextHeaderAtom::parser()
{
	return Error_TODO;
}

void PST_TextHeaderAtom::clearParserData()
{
	textType = 0;
}

int PST_TextHeaderAtom::priority()
{
	return 0;
}
