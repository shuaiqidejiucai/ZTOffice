#include "pst_slideviewinfo.h"
#include "pstsearch.h"
PST_SlideViewInfo::PST_SlideViewInfo(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_SlideViewInfo::parser(PSTSearch* pSearchPtr)
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
		case RT_SlideViewInfoAtom:
		{
			QSharedPointer<PST_SlideViewInfoAtom> slideViewInfoAtomPtr(new PST_SlideViewInfoAtom(m_srcData, stVar));
			slideViewInfoAtomList.append(slideViewInfoAtomPtr);
			addChildNodePtr(slideViewInfoAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, slideViewInfoAtomPtr);
		}
		break;
		case RT_ViewInfoAtom:
		{
			QSharedPointer<PST_ViewInfoAtom> viewInfoAtomPtr(new PST_ViewInfoAtom(m_srcData, stVar));
			viewInfoAtomList.append(viewInfoAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, viewInfoAtomPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_SlideViewInfo::clearParserData()
{
	slideViewInfoAtomList.clear();
	viewInfoAtomList.clear();
}

int PST_SlideViewInfo::priority()
{
	return 0;
}

PST_SlideViewInfoAtom::PST_SlideViewInfoAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_SlideViewInfoAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_SlideViewInfoAtom::clearParserData()
{
}

int PST_SlideViewInfoAtom::priority()
{
	return 0;
}
