#include "pst_gridspacing10atom.h"

PST_GridSpacing10Atom::PST_GridSpacing10Atom(const QByteArray& srcData, const ST_Variable& var)
    : PST_Base(srcData, var)
{
}

int PST_GridSpacing10Atom::parser(PSTSearch* pSearchPtr)
{
    return Error_TODO;
}

void PST_GridSpacing10Atom::clearParserData()
{
}

int PST_GridSpacing10Atom::priority()
{
    return 0;
}
