#include "odraw_officeartbstorecontainer.h"
#include "pstsearch.h"
#include "pst_msofbtbse.h"
ODRAW_OfficeArtBStoreContainer::ODRAW_OfficeArtBStoreContainer(const QByteArray& srcData, const ST_Variable& var):PST_Base(srcData,var)
{

}

int ODRAW_OfficeArtBStoreContainer::parser(PSTSearch* pSeaechPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}

		switch (ST_TP(stVar))
		{ 
		case COMMON_OfficeArtFBSE:
		{
			QSharedPointer<PST_MSOfbtBSE> msoFbtBSE = QSharedPointer<PST_MSOfbtBSE>::create(m_srcData, stVar);
			msoBtBsePtrList.append(msoFbtBSE);
			addChildNodePtr(msoFbtBSE);
			if (pSeaechPtr) pSeaechPtr->insertRecordMap(stVar.originPos, msoFbtBSE);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return Error_SuccessType;
}

void ODRAW_OfficeArtBStoreContainer::clearParserData()
{
	msoBtBsePtrList.clear();

}

int ODRAW_OfficeArtBStoreContainer::priority()
{
	return 0;
}
