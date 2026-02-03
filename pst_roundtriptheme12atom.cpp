#include "pst_roundtriptheme12atom.h"

PST_RoundTripTheme12Atom::PST_RoundTripTheme12Atom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_RoundTripTheme12Atom::parser()
{
	return Error_TODO;
}

void PST_RoundTripTheme12Atom::clearParserData()
{
}

int PST_RoundTripTheme12Atom::priority()
{
	return 0;
}
