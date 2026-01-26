#include "pst_list.h"

PST_List::PST_List(const QByteArray &srcData):PST_Base(srcData) {}

int PST_List::parser()
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
		case RT_NormalViewSetInfo9:
		{
			QSharedPointer<PST_NormalViewSetInfo> normalViewSetInfo(new PST_NormalViewSetInfo(m_srcData));
			normalViewSetInfo->setSTVar(stVar);
			normalViewSetInfoList.append(normalViewSetInfo);
		}
			break;
		case RT_NotesTextViewInfo9:
		{
			QSharedPointer<PST_NotesTextViewInfo> notesTextViewInfo (new PST_NotesTextViewInfo(m_srcData));
			notesTextViewInfo->setSTVar(stVar);
			notesTxtViewInfoList.append(notesTextViewInfo);
		}
			break;
		case RT_SlideViewInfo:
		{
			QSharedPointer<PST_SlideViewInfo> slideViewInfo(new PST_SlideViewInfo(m_srcData));
			slideViewInfo->setSTVar(stVar);
			slideViewInfoList.append(slideViewInfo);
		}
			break;
		case RT_ProgTags:
		{
			QSharedPointer<PST_ProgTags> progTagsPtr(new PST_ProgTags(m_srcData));
			progTagsPtr->setSTVar(stVar);
			progTagsList.append(progTagsPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
