#include "pst_ppdrawinggroup.h"
#include "pstsearch.h"
#include "pst_drawinggroupcontainer.h"
PST_PPDrawingGroup::PST_PPDrawingGroup(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_PPDrawingGroup::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}

		if (ST_TP(stVar) == COMMON_OfficeArtDggContainer)
		{
			QSharedPointer<PST_DrawingGroupContainer> dwingGroupContainer(new PST_DrawingGroupContainer(m_srcData, stVar));
			dwGroupContainterList.append(dwingGroupContainer);
			addChildNodePtr(dwingGroupContainer);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, dwingGroupContainer);
		}
		
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return Error_SuccessType;
}

void PST_PPDrawingGroup::clearParserData()
{
	dwGroupContainterList.clear();
}

int PST_PPDrawingGroup::priority()
{
	return 0;
}
