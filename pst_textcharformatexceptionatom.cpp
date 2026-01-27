#include "pst_textcharformatexceptionatom.h"

PST_TextCharFormatExceptionAtom::PST_TextCharFormatExceptionAtom(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{

}

int PST_TextCharFormatExceptionAtom::parser()
{
    return 0;
}
