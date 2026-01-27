#include "pst_txmasterstyleatom.h"

PST_TxMasterStyleAtom::PST_TxMasterStyleAtom(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{

}

int PST_TxMasterStyleAtom::parser()
{
    return 0;
}
