#include "pst_roundtripcolormapping12atom.h"

PST_RoundTripColorMapping12Atom::PST_RoundTripColorMapping12Atom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_RoundTripColorMapping12Atom::parser()
{
	return Error_TODO;
}

void PST_RoundTripColorMapping12Atom::clearParserData()
{
}

int PST_RoundTripColorMapping12Atom::priority()
{
	return 0;
}
