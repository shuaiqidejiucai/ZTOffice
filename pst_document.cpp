#include "pst_document.h"
#include "zttools.h"
PST_Document::PST_Document(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_Document::parser()
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
		case RT_DocumentAtom:
		{
			documentAtomPtr = QSharedPointer<PST_DocumentAtom>::create(m_srcData);
			documentAtomPtr->setSTVar(stVar);
		}
			break;
		case RT_ExternalObjectList:
		{
			QSharedPointer<PST_ExObjList> exObjPtr(new PST_ExObjList(m_srcData));
			exObjPtr->setSTVar(stVar);

		}
			break;
		case RT_Environment:
		{
			QSharedPointer<PST_Environment> envPtr(new PST_Environment(m_srcData));
			envPtr->setSTVar(stVar);
			envmentList.append(envPtr);
		}
			break;
		case RT_DrawingGroup:
		{
			QSharedPointer<PST_PPDrawingGroup> dwingGroupPtr(new PST_PPDrawingGroup(m_srcData));
			dwingGroupPtr->setSTVar(stVar);
			ppdwGroupList.append(dwingGroupPtr);
		}
			break;
		case RT_SlideListWithText:
		{
			QSharedPointer<PST_SlideListWithText> slideListWithTextPtr(new PST_SlideListWithText(m_srcData));
			slideListWithTextPtr->setSTVar(stVar);
			slideListWithTxtList.append(slideListWithTextPtr);
		}
		break;
		case RT_List:
		{
			QSharedPointer<PST_List> pstListPtr(new PST_List(m_srcData));
			pstListPtr->setSTVar(stVar);
			PSTList.append(pstListPtr);
		}
		break;
		case RT_HeadersFooters:
		{
			QSharedPointer<PST_HeadersFooters> headersFootersPtr(new PST_HeadersFooters(m_srcData));
			headersFootersPtr->setSTVar(stVar);
			headersFootersList.append(headersFootersPtr);
		}
		case RT_RoundTripCustomTableStyles12Atom:
		{
			QSharedPointer<PST_RoundTripCustomTableStyles12> roundTripTableStylePtr(new PST_RoundTripCustomTableStyles12(m_srcData));
			roundTripTableStylePtr->setSTVar(stVar);
			roundTripTableStyleList.append(roundTripTableStylePtr);
		}
			break;
		case RT_EndDocumentAtom:
		{
			endDocumentAtom = QSharedPointer<PST_EndDocumentAtom>::create(m_srcData);
			endDocumentAtom->setSTVar(stVar);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
