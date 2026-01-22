#include "pst_exobjlist.h"

PST_ExObjList::PST_ExObjList(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_ExObjList::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return -1;
		}
		switch (ST_TP(stVar))
		{
		case RT_ExternalObjectListAtom:
		{
			exObjListAtomPtr = QSharedPointer<PST_ExternalObjectListAtom>::create(m_srcData);
			exObjListAtomPtr->setSTVar(stVar);
		}
			break;
		default:
			break;
		}

		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
