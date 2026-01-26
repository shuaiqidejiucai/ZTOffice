#include "pst_slideviewinfo.h"

PST_SlideViewInfo::PST_SlideViewInfo(const QByteArray &srcData):PST_Base(srcData) {}

int PST_SlideViewInfo::parser()
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
		case RT_SlideViewInfoAtom:
		{
			QSharedPointer<PST_SlideViewInfoAtom> slideViewInfoAtomPtr(new PST_SlideViewInfoAtom(m_srcData));
			slideViewInfoAtomPtr->setSTVar(stVar);
			slideViewInfoAtomList.append(slideViewInfoAtomPtr);
		}
		break;
		case RT_ViewInfoAtom:
		{
			QSharedPointer<PST_ViewInfoAtom> slideViewInfoAtomPtr(new PST_ViewInfoAtom(m_srcData));
			slideViewInfoAtomPtr->setSTVar(stVar);
			viewInfoAtomList.append(slideViewInfoAtomPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}

PST_SlideViewInfoAtom::PST_SlideViewInfoAtom(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_SlideViewInfoAtom::parser()
{
	return 0;
}
