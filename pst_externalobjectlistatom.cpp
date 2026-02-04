#include "pst_externalobjectlistatom.h"

PST_ExternalObjectListAtom::PST_ExternalObjectListAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_ExternalObjectListAtom::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	qint32 exObjIdSeed = GetFlagData<qint32>(m_srcData, pos);
	return Error_SuccessType;
}

void PST_ExternalObjectListAtom::clearParserData()
{

}

int PST_ExternalObjectListAtom::priority()
{
	return 0;
}
