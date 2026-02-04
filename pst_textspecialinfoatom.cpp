#include "pst_textspecialinfoatom.h"

PST_TextSpecialInfoAtom::PST_TextSpecialInfoAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_TextSpecialInfoAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_TextSpecialInfoAtom::clearParserData()
{
}

int PST_TextSpecialInfoAtom::priority()
{
	return 0;
}
