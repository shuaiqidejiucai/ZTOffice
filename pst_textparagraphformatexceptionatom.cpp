#include "pst_textparagraphformatexceptionatom.h"

PST_TextParagraphFormatExceptionAtom::PST_TextParagraphFormatExceptionAtom(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData, var)
{

}

int PST_TextParagraphFormatExceptionAtom::parser()
{
    return 0;
}
