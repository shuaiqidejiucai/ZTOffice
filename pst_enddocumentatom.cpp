#include "pst_enddocumentatom.h"

PST_EndDocumentAtom::PST_EndDocumentAtom(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData, var)
{
}

int PST_EndDocumentAtom::parser()
{
    return 0;
}
