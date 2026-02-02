#include "pst_genericdatemetacharatom.h"

PST_GenericDateMetaCharAtom::PST_GenericDateMetaCharAtom(const QByteArray& srcData, const ST_Variable& var)
:PST_Base(srcData, var){}

int PST_GenericDateMetaCharAtom::parser()
{
    return Error_TODO;
}

void PST_GenericDateMetaCharAtom::clearParserData()
{
}
