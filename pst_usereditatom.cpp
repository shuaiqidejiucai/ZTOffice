#include "pst_usereditatom.h"

PST_UserEditAtom::PST_UserEditAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var), lastSlideIdRef(0),version(0),minorVersion(0),majorVersion(0),
	offsetLastEdit(0),offsetPersistDirectory(0),docPersistIdRef(0),persistIdSeed(0),
	lastView(0),unused(0),encryptSessionPersistIdRef(0)
{

}

int PST_UserEditAtom::parser()
{
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
	return Error_SuccessType;
}

void PST_UserEditAtom::clearParserData()
{
	lastSlideIdRef = 0;
	/*quint32 version : 16;
	minorVersion : 8;
	majorVersion : 8;*/
	version = 0;
	minorVersion = 0;
	majorVersion = 0;

	offsetLastEdit = 0;
	offsetPersistDirectory = 0;
	docPersistIdRef = 0;
	persistIdSeed = 0;
	lastView = 0;
	unused = 0;
	encryptSessionPersistIdRef = 0;
}
