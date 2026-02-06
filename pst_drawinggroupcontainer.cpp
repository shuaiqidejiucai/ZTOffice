#include "pst_drawinggroupcontainer.h"
#include "pstsearch.h"
#include "odraw_officeartbstorecontainer.h"
#include "pst_msofbtopt.h"
#include "odraw_officeartsplitmenucolorcontainer.h"
PST_DrawingGroupContainer::PST_DrawingGroupContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

PST_DrawingGroupAtom::PST_DrawingGroupAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_DrawingGroupAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_DrawingGroupAtom::clearParserData()
{
}

int PST_DrawingGroupAtom::priority()
{
	return 0;
}

int PST_DrawingGroupContainer::parser(PSTSearch* pSearchPtr)
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
		case COMMON_OfficeArtFDGGBlock:
		{
			dwGroupAtom = QSharedPointer<PST_DrawingGroupAtom>::create(m_srcData, stVar);
			addChildNodePtr(dwGroupAtom);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, dwGroupAtom);
		}
		break;
		case COMMON_OfficeArtBStoreContainer:
		{
			odrawOABSContainer = QSharedPointer<ODRAW_OfficeArtBStoreContainer>::create(m_srcData, stVar);
			addChildNodePtr(odrawOABSContainer);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, odrawOABSContainer);
		}
			break;
		case COMMON_OfficeArtFOPT:
		{
			msofbtOPT = QSharedPointer<PST_MSOfbtOPT>::create(m_srcData, stVar);
			addChildNodePtr(msofbtOPT);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, msofbtOPT);
		}
			break;
		case COMMON_OfficeArtSplitMenuColorContainer:
		{
			oasColorContainter = QSharedPointer<ODRAW_OfficeArtSplitMenuColorContainer>::create(m_srcData, stVar);
			addChildNodePtr(oasColorContainter);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, oasColorContainter);
		}
			break;
		default:
			break;
		} 


		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_DrawingGroupContainer::clearParserData()
{
	dwGroupAtom.clear();
	odrawOABSContainer.clear();
	msofbtOPT.clear();
	oasColorContainter.clear();
}

int PST_DrawingGroupContainer::priority()
{
	return 0;
}


