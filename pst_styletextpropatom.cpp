#include "pst_styletextpropatom.h"

PST_StyleTextPropAtom::PST_StyleTextPropAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_StyleTextPropAtom::parser()
{
	return Error_TODO;
}

void PST_StyleTextPropAtom::clearParserData()
{
}
