#include "pst_drawinggroupcontainer.h"

PST_DrawingGroupContainer::PST_DrawingGroupContainer(const QByteArray &srcData):PST_Base(srcData)
{

}

PST_DrawingGroupAtom::PST_DrawingGroupAtom(const QByteArray& srcData) :PST_Base(srcData)
{

}

int PST_DrawingGroupAtom::parser()
{
	return 0;
}

int PST_DrawingGroupContainer::parser()
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
		case COMMON_OfficeArtFDGGBlock:
		{
			dwGroupAtom = QSharedPointer<PST_DrawingGroupAtom>::create(m_srcData);
			dwGroupAtom->setSTVar(stVar);
		}
		break;
		case COMMON_OfficeArtBStoreContainer:
		{
			odrawOABSContainer = QSharedPointer<ODRAW_OfficeArtBStoreContainer>::create(m_srcData);
			odrawOABSContainer->setSTVar(stVar);
		}
			break;
		case COMMON_OfficeArtFOPT:
		{
			msofbtOPT = QSharedPointer<PST_MSOfbtOPT>::create(m_srcData);
			msofbtOPT->setSTVar(stVar);
		}
			break;
		case COMMON_OfficeArtSplitMenuColorContainer:
		{
			oasColorContainter = QSharedPointer<ODRAW_OfficeArtSplitMenuColorContainer>::create(m_srcData);
			oasColorContainter->setSTVar(stVar);
		}
			break;
		default:
			break;
		} 


		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}


