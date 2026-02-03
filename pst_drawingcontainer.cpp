#include "pst_drawingcontainer.h"

PST_DrawingContainer::PST_DrawingContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_DrawingContainer::parser()
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
		case COMMON_OfficeArtFDG:
		{
			officeArtFDG = QSharedPointer<PST_OfficeArtFDG>::create(m_srcData, stVar);
			addChildNodePtr(officeArtFDG);
		}
		break;
		case COMMON_OfficeArtSpgrContainer:
		{
			groupShapeContainer = QSharedPointer<PST_GroupShapeContainer>::create(m_srcData, stVar);
			addChildNodePtr(groupShapeContainer);
		}
			break;
		case COMMON_OfficeArtSpContainer:
		{
			shapeContainer = QSharedPointer<PST_ShapeContainer>::create(m_srcData, stVar);
			addChildNodePtr(shapeContainer);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_DrawingContainer::clearParserData()
{
	officeArtFDG.clear();
	groupShapeContainer.clear();
	shapeContainer.clear();
}

int PST_DrawingContainer::priority()
{
	return 0;
}
