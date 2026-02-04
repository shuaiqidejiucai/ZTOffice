#include "pst_textspecialinfodefaultatom.h"

PST_TextSpecialInfoDefaultAtom::PST_TextSpecialInfoDefaultAtom(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{

}

int PST_TextSpecialInfoDefaultAtom::parser(PSTSearch* pSearchPtr)
{
    return Error_TODO;
}

void PST_TextSpecialInfoDefaultAtom::clearParserData()
{
}

int PST_TextSpecialInfoDefaultAtom::priority()
{
    return 0;
}
