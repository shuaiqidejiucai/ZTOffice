#include "pst_slide.h"
#include "pstsearch.h"
#include "pst_slideatom.h"
#include "pst_ppdrawing.h"
#include "pst_colorschemeatom.h"
#include "pst_progtags.h"
#include "pst_roundtripcontentmasterid12atom.h"
PST_Slide::PST_Slide(const QByteArray& srcData, const ST_Variable& var):PST_Base(srcData, var)
{

}

int PST_Slide::parser(PSTSearch* pSearchPtr)
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
			addChildNodePtr(slideAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, slideAtomPtr);
		}
		break;
		case RT_Drawing:
		{
			ppdwingPtr = QSharedPointer<PST_PPDrawing>::create(m_srcData, stVar);
			addChildNodePtr(ppdwingPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, ppdwingPtr);
		}
		break;
		case RT_ColorSchemeAtom:
		{
			colorSchemeAtomPtr = QSharedPointer<PST_ColorSchemeAtom>::create(m_srcData, stVar);
			addChildNodePtr(colorSchemeAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, colorSchemeAtomPtr);
		}
		break;
		case RT_ProgTags:
		{
			proTagsPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
			addChildNodePtr(proTagsPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, proTagsPtr);
		}
		break;
		case RT_RoundTripContentMasterId12Atom:
		{
			roundTripContentMasterId12AtomPtr = QSharedPointer<PST_RoundTripContentMasterId12Atom>::create(m_srcData, stVar);
			addChildNodePtr(roundTripContentMasterId12AtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, roundTripContentMasterId12AtomPtr);
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
