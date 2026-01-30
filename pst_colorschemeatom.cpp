#include "pst_colorschemeatom.h"

PST_ColorSchemeAtom::PST_ColorSchemeAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ColorSchemeAtom::parser()
{
	//TODO:ÑÕÉ«½âÎö
	m_isParser = true;
	return Error_BinType;
}

void PST_ColorSchemeAtom::clearParserData()
{
	m_isParser = false;
}
