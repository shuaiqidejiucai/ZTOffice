#include "pst_drawinggroupcontainer.h"

PST_DrawingGroupContainer::PST_DrawingGroupContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

PST_DrawingGroupAtom::PST_DrawingGroupAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_DrawingGroupAtom::parser()
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

int PST_DrawingGroupContainer::parser()
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
		}
		break;
		case COMMON_OfficeArtBStoreContainer:
		{
			odrawOABSContainer = QSharedPointer<ODRAW_OfficeArtBStoreContainer>::create(m_srcData, stVar);
			addChildNodePtr(odrawOABSContainer);
		}
			break;
		case COMMON_OfficeArtFOPT:
		{
			msofbtOPT = QSharedPointer<PST_MSOfbtOPT>::create(m_srcData, stVar);
			addChildNodePtr(msofbtOPT);
		}
			break;
		case COMMON_OfficeArtSplitMenuColorContainer:
		{
			oasColorContainter = QSharedPointer<ODRAW_OfficeArtSplitMenuColorContainer>::create(m_srcData, stVar);
			addChildNodePtr(oasColorContainter);
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


