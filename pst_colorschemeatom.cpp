#include "pst_colorschemeatom.h"

PST_ColorSchemeAtom::PST_ColorSchemeAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ColorSchemeAtom::parser()
{
	//TODO:ÑÕÉ«½âÎö
	return Error_TODO;
}

void PST_ColorSchemeAtom::clearParserData()
{
}

int PST_ColorSchemeAtom::priority()
{
	return 0;
}
