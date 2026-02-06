#include "pst_ppdrawing.h"
#include "pstsearch.h"
#include "pst_drawingcontainer.h"
PST_PPDrawing::PST_PPDrawing(const QByteArray &srcData, const ST_Variable& var):PST_Base(srcData,var) {}

int PST_PPDrawing::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(stVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}
		switch (ST_TP(stVar))
		{
		case COMMON_OfficeArtDgContainer:
		{
			dwingContinerPtr = QSharedPointer<PST_DrawingContainer>::create(m_srcData, stVar);
			addChildNodePtr(dwingContinerPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, dwingContinerPtr);
		}
		break;
		default:
			break;
			
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(stVar));
	return Error_SuccessType;
}

void PST_PPDrawing::clearParserData()
{
	dwingContinerPtr.clear();
}

int PST_PPDrawing::priority()
{
	return 0;
}
