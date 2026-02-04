#include "pst_textparagraphformatexceptionatom.h"

PST_TextParagraphFormatExceptionAtom::PST_TextParagraphFormatExceptionAtom(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData, var)
{

}

int PST_TextParagraphFormatExceptionAtom::parser(PSTSearch* pSearchPtr)
{
    return Error_TODO;
}

void PST_TextParagraphFormatExceptionAtom::clearParserData()
{
}

int PST_TextParagraphFormatExceptionAtom::priority()
{
    return 0;
}
