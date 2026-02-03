#include "pst_shapeclientcontainer.h"

PST_ShapeClientContainer::PST_ShapeClientContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ShapeClientContainer::parser()
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
	return Error_SuccessType;
}

void PST_ShapeClientContainer::clearParserData()
{
	oePlaceHolderAtom.clear();
	//QSharedPointer<PST_RoundTripHFPlaceholder12Atom> roundTripHF12Atom;
	//QSharedPointer<PST_ExternalObjectRefAtom> exObjRefAtom;
	progTagsPtr.clear();
}

int PST_ShapeClientContainer::priority()
{
	return 0;
}
