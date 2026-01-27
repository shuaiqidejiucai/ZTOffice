#include "fopte.h"

Fopte::Fopte(const QByteArray& srcData, const ST_Variable& var) : PST_Base(srcData, var) {}

int Fopte::parser()
{
    quint32 pos = ST_SP(m_STVar);
    quint16 value = GetFlagData<quint16>(m_srcData, pos);
    pid = value & 0x3FFF;
    fBid = (value >> 14) & 0x1;
    fComplex = (value >> 15) & 0x1;
    op = GetFlagData<quint32>(m_srcData, pos);
    return 0;
}

FOPTEComplex::FOPTEComplex(const QByteArray& srcData, const ST_Variable& var) : PST_Base(srcData, var)
{

}

int FOPTEComplex::parser()
{
    return 0;
}
