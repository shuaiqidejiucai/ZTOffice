#include "pst_oeplaceholderatom.h"

PST_OEPlaceHolderAtom::PST_OEPlaceHolderAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_OEPlaceHolderAtom::parser()
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	PlacementID = GetFlagData<quint32>(m_srcData, pos);
	PlaceholderID = GetFlagData<quint8>(m_srcData, pos);
	Size = GetFlagData<quint8>(m_srcData, pos);
	Unused = GetFlagData<quint16>(m_srcData, pos);
	return Error_SuccessType;
}

void PST_OEPlaceHolderAtom::clearParserData()
{
	PlacementID = 0;
	PlaceholderID = 0;
	Size = 0;
	Unused = 0;
}
