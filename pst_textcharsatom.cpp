#include "pst_textcharsatom.h"

PST_TextCharsAtom::PST_TextCharsAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_TextCharsAtom::parser()
{
	return Error_TODO;
}

void PST_TextCharsAtom::clearParserData()
{
}
