#include "pst_txmasterstyleatom.h"

PST_TxMasterStyleAtom::PST_TxMasterStyleAtom(const QByteArray& srcData, const ST_Variable& var)
    :PST_Base(srcData,var)
{

}

int PST_TxMasterStyleAtom::parser(PSTSearch* pSeaechPtr)
{
    return Error_TODO;
}

void PST_TxMasterStyleAtom::clearParserData()
{
}

int PST_TxMasterStyleAtom::priority()
{
    return 0;
}
