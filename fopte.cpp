#include "fopte.h"

Fopte::Fopte(const QByteArray& srcData) : PST_Base(srcData) {}

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

FOPTEComplex::FOPTEComplex(const QByteArray& srcData): PST_Base(srcData)
{

}

int FOPTEComplex::parser()
{
    return 0;
}
