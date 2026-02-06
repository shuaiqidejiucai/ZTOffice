#include "pst_roundtripnotesmastertextstyles12atom.h"

PST_RoundTripNotesMasterTextStyles12Atom::PST_RoundTripNotesMasterTextStyles12Atom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{
}

int PST_RoundTripNotesMasterTextStyles12Atom::parser(PSTSearch* pSearchPtr)
{
	return 0;
}

void PST_RoundTripNotesMasterTextStyles12Atom::clearParserData()
{
}

int PST_RoundTripNotesMasterTextStyles12Atom::priority()
{
	return 0;
}
