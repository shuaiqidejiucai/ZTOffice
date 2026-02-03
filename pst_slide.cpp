#include "pst_slide.h"

PST_Slide::PST_Slide(const QByteArray& srcData, const ST_Variable& var):PST_Base(srcData, var)
{

}

int PST_Slide::parser()
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
		case RT_SlideAtom:
		{
			slideAtomPtr = QSharedPointer<PST_SlideAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_Drawing:
		{
			ppdwingPtr = QSharedPointer<PST_PPDrawing>::create(m_srcData, stVar);
		}
		break;
		case RT_ColorSchemeAtom:
		{
			colorSchemeAtomPtr = QSharedPointer<PST_ColorSchemeAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_ProgTags:
		{
			proTagsPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
		}
		break;
		case RT_RoundTripContentMasterId12Atom:
		{
			roundTripContentMasterId12AtomPtr = QSharedPointer<PST_RoundTripContentMasterId12Atom>::create(m_srcData, stVar);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));

	return Error_SuccessType;
}

void PST_Slide::clearParserData()
{
	slideAtomPtr.clear();
	ppdwingPtr.clear();
	colorSchemeAtomPtr.clear();
	proTagsPtr.clear();
	roundTripContentMasterId12AtomPtr.clear();
}

int PST_Slide::priority()
{
	return 0;
}
