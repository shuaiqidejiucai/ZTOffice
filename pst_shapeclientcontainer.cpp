#include "pst_shapeclientcontainer.h"

PST_ShapeClientContainer::PST_ShapeClientContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ShapeClientContainer::parser()
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
		case RT_PlaceholderAtom:
		{
			oePlaceHolderAtom = QSharedPointer<PST_OEPlaceHolderAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_ProgTags:
		{
			progTagsPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
