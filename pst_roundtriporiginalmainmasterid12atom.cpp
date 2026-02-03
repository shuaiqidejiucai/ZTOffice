#include "pst_roundtriporiginalmainmasterid12atom.h"

PST_RoundTripOriginalMainMasterId12Atom::PST_RoundTripOriginalMainMasterId12Atom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{
}

int PST_RoundTripOriginalMainMasterId12Atom::parser()
{
	return Error_TODO;
}

void PST_RoundTripOriginalMainMasterId12Atom::clearParserData()
{
}

int PST_RoundTripOriginalMainMasterId12Atom::priority()
{
	return 0;
}
