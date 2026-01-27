#include "pst_viewinfoatom.h"

PST_ViewInfoAtom::PST_ViewInfoAtom(const QByteArray &srcData, const ST_Variable& var)
    :PST_Base(srcData, var)
{

}

int PST_ViewInfoAtom::parser()
{
    return 0;
}
