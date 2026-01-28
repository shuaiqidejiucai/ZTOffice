#include "pst_usereditatom.h"

PST_UserEditAtom::PST_UserEditAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_UserEditAtom::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	lastSlideIdRef = GetFlagData<quint32>(m_srcData, pos);
	version = GetFlagData<quint16>(m_srcData, pos);
	minorVersion = GetFlagData<quint8>(m_srcData, pos);
	majorVersion = GetFlagData<quint8>(m_srcData, pos);
	offsetLastEdit = GetFlagData<quint32>(m_srcData, pos);
	offsetPersistDirectory = GetFlagData<quint32>(m_srcData, pos);
	docPersistIdRef = GetFlagData<quint32>(m_srcData, pos);
	persistIdSeed = GetFlagData<quint32>(m_srcData, pos);
	lastView = GetFlagData<quint16>(m_srcData, pos);
	unused = GetFlagData<quint16>(m_srcData, pos);
	encryptSessionPersistIdRef = GetFlagData<quint32>(m_srcData, pos);
	return 0;
}
