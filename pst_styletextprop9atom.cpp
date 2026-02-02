#include "pst_styletextprop9atom.h"

PST_StyleTextProp9Atom::PST_StyleTextProp9Atom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_StyleTextProp9Atom::parser()
{
	return Error_TODO;
}

void PST_StyleTextProp9Atom::clearParserData()
{
}
