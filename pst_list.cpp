#include "pst_list.h"
#include "pstsearch.h"
#include "pst_normalviewsetinfo.h"
#include "pst_notestextviewinfo.h"
#include "pst_slideviewinfo.h"
#include "pst_progtags.h"
PST_List::PST_List(const QByteArray &srcData, const ST_Variable& var):PST_Base(srcData, var) {}

int PST_List::parser(PSTSearch* pSearchPtr)
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
		case RT_NormalViewSetInfo9:
		{
			QSharedPointer<PST_NormalViewSetInfo> normalViewSetInfo(new PST_NormalViewSetInfo(m_srcData, stVar));
			normalViewSetInfoList.append(normalViewSetInfo);
			addChildNodePtr(normalViewSetInfo);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, normalViewSetInfo);
		}
			break;
		case RT_NotesTextViewInfo9:
		{
			QSharedPointer<PST_NotesTextViewInfo> notesTextViewInfo (new PST_NotesTextViewInfo(m_srcData, stVar));
			notesTxtViewInfoList.append(notesTextViewInfo);
			addChildNodePtr(notesTextViewInfo);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, notesTextViewInfo);
		}
			break;
		case RT_SlideViewInfo:
		{
			QSharedPointer<PST_SlideViewInfo> slideViewInfo(new PST_SlideViewInfo(m_srcData, stVar));
			slideViewInfoList.append(slideViewInfo);
			addChildNodePtr(slideViewInfo);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, slideViewInfo);
		}
			break;
		case RT_ProgTags:
		{
			QSharedPointer<PST_ProgTags> progTagsPtr(new PST_ProgTags(m_srcData, stVar));
			progTagsList.append(progTagsPtr);
			addChildNodePtr(progTagsPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, progTagsPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_List::clearParserData()
{
	normalViewSetInfoList.clear();
	notesTxtViewInfoList.clear();
	slideViewInfoList.clear();
	progTagsList.clear();
}

int PST_List::priority()
{
	return 0;
}
