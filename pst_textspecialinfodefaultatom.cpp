#include "pst_textspecialinfodefaultatom.h"

PST_TextSpecialInfoDefaultAtom::PST_TextSpecialInfoDefaultAtom(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{

}

int PST_TextSpecialInfoDefaultAtom::parser()
{
    return 0;
}
