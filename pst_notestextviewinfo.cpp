#include "pst_notestextviewinfo.h"

PST_NotesTextViewInfo::PST_NotesTextViewInfo(const QByteArray &srcData):PST_Base(srcData) {}

int PST_NotesTextViewInfo::parser()
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
		case RT_ViewInfoAtom:
		{
			QSharedPointer<PST_ViewInfoAtom> viewInfoAtomPtr(new PST_ViewInfoAtom(m_srcData));
			viewInfoAtomPtr->setSTVar(stVar);
			viewInfoAtomList.append(viewInfoAtomPtr);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}


