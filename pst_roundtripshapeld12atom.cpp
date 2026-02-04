#include "pst_roundtripshapeld12atom.h"

PST_RoundTripShapeld12Atom::PST_RoundTripShapeld12Atom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_RoundTripShapeld12Atom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_RoundTripShapeld12Atom::clearParserData()
{
}

int PST_RoundTripShapeld12Atom::priority()
{
	return 0;
}
