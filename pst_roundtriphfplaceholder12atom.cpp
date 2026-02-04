#include "pst_roundtriphfplaceholder12atom.h"

PST_RoundTripHFPlaceholder12Atom::PST_RoundTripHFPlaceholder12Atom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_RoundTripHFPlaceholder12Atom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_RoundTripHFPlaceholder12Atom::clearParserData()
{

}

int PST_RoundTripHFPlaceholder12Atom::priority()
{
	return 0;
}
