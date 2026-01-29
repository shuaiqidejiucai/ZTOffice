#include "pst_ppdrawing.h"

PST_PPDrawing::PST_PPDrawing(const QByteArray &srcData, const ST_Variable& var):PST_Base(srcData,var) {}

int PST_PPDrawing::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(stVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return -1;
		}
		switch (ST_TP(stVar))
		{
		case COMMON_OfficeArtDgContainer:
		{
			dwingContiner = QSharedPointer<PST_DrawingContainer>::create(m_srcData, stVar);
		}
		break;
		default:
			break;
			
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(stVar));
	return 0;
}
