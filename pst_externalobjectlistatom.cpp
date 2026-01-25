#include "pst_externalobjectlistatom.h"

PST_ExternalObjectListAtom::PST_ExternalObjectListAtom(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_ExternalObjectListAtom::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	qint32 exObjIdSeed = GetFlagData<qint32>(m_srcData, pos);
	return 0;
}
