#include "pst_slideviewinfo.h"

PST_SlideViewInfo::PST_SlideViewInfo(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_SlideViewInfo::parser()
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
		}
		break;
		case RT_ViewInfoAtom:
		{
			QSharedPointer<PST_ViewInfoAtom> slideViewInfoAtomPtr(new PST_ViewInfoAtom(m_srcData, stVar));
			viewInfoAtomList.append(slideViewInfoAtomPtr);
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

int PST_SlideViewInfoAtom::parser()
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
