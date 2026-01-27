#include "pst_ppdrawinggroup.h"

PST_PPDrawingGroup::PST_PPDrawingGroup(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_PPDrawingGroup::parser()
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

		if (ST_TP(stVar) == COMMON_OfficeArtDggContainer)
		{
			QSharedPointer<PST_DrawingGroupContainer> dwingGroupContainer(new PST_DrawingGroupContainer(m_srcData, stVar));
			dwGroupContainterList.append(dwingGroupContainer);
		}
		
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return 0;
}
