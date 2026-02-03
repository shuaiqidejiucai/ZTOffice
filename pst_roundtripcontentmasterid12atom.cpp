#include "pst_roundtripcontentmasterid12atom.h"

PST_RoundTripContentMasterId12Atom::PST_RoundTripContentMasterId12Atom(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData, var) {}

int PST_RoundTripContentMasterId12Atom::parser()
{
    return Error_TODO;
}

void PST_RoundTripContentMasterId12Atom::clearParserData()
{
}

int PST_RoundTripContentMasterId12Atom::priority()
{
    return 0;
}
