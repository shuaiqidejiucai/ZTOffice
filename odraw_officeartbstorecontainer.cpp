#include "odraw_officeartbstorecontainer.h"

ODRAW_OfficeArtBStoreContainer::ODRAW_OfficeArtBStoreContainer(const QByteArray& srcData):PST_Base(srcData)
{

}

int ODRAW_OfficeArtBStoreContainer::parser()
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
		case COMMON_OfficeArtFBSE:
		{
			QSharedPointer<PST_MSOfbtBSE> msoFbtBSE = QSharedPointer<PST_MSOfbtBSE>::create(m_srcData);
			msoFbtBSE->setSTVar(stVar);
			msoBtBsePtrList.append(msoFbtBSE);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return 0;
}
