#include "pst_msofbtbse.h"

PST_MSOfbtBSE::PST_MSOfbtBSE(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_MSOfbtBSE::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	quint8 btWin32 = GetFlagData<quint8>(m_srcData, pos);
	quint8 btMacOS = GetFlagData<quint8>(m_srcData, pos);
	rgUid = m_srcData.mid(pos, 16);
	pos += 16;
	quint16 Tag = GetFlagData<quint16>(m_srcData, pos);
	quint32 Size = GetFlagData<quint32>(m_srcData, pos);
	quint32 cRef = GetFlagData<quint32>(m_srcData, pos);
	quint32 foDelay = GetFlagData<quint32>(m_srcData, pos);
	quint8 Usage = GetFlagData<quint8>(m_srcData, pos);
	quint8 cbName = GetFlagData<quint8>(m_srcData, pos);
	quint8 Unused2 = GetFlagData<quint8>(m_srcData, pos);
	quint8 Unused3 = GetFlagData<quint8>(m_srcData, pos);
    return 0;
}
