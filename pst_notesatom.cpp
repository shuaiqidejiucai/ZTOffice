#include "pst_notesatom.h"

PST_NotesAtom::PST_NotesAtom(const QByteArray& srcData, const ST_Variable& var):PST_Base(srcData,var) {}

int PST_NotesAtom::parser()
{
    return Error_BinType;
}

void PST_NotesAtom::clearParserData()
{
}
