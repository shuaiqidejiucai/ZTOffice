#include "pst_groupshapecontainer.h"

PST_GroupShapeContainer::PST_GroupShapeContainer(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_GroupShapeContainer::parser()
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
		case COMMON_OfficeArtSpContainer:
		{
			QSharedPointer<PST_ShapeContainer> shapContainerPtr(new PST_ShapeContainer(m_srcData, stVar));
			shapeContainerList.append(shapContainerPtr);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_GroupShapeContainer::clearParserData()
{
	shapeContainerList.clear();
}
