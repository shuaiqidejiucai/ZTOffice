#include "pst_textruleratom.h"

PST_TextRulerAtom::PST_TextRulerAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_TextRulerAtom::parser()
{
	return Error_TODO;
}

void PST_TextRulerAtom::clearParserData()
{
}
