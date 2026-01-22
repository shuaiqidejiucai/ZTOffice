#include "pst_externalobjectlistatom.h"

PST_ExternalObjectListAtom::PST_ExternalObjectListAtom(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_ExternalObjectListAtom::parser()
{
	/*quint32 pos = ST_SP(m_STVar);
	qint32 exObjIdSeed = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + ST_SP(stVar)));*/
	return 0;
}
