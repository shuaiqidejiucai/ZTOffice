#include "pst_roundtripheaderfooterdefaults12atom.h"

PST_RoundTripHeaderFooterDefaults12Atom::PST_RoundTripHeaderFooterDefaults12Atom(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData,var) {}

int PST_RoundTripHeaderFooterDefaults12Atom::parser()
{
    return Error_TODO;
}

void PST_RoundTripHeaderFooterDefaults12Atom::clearParserData()
{
}
