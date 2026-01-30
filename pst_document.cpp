#include "pst_document.h"
#include "zttools.h"
PST_Document::PST_Document(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_Document::parser()
{
	if (m_isParser)
	{
		clearParserData();
	}
	m_isParser = true;
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
		case RT_DocumentAtom:
		{
			documentAtomPtr = QSharedPointer<PST_DocumentAtom>::create(m_srcData, stVar);
		}
			break;
		case RT_ExternalObjectList:
		{
			QSharedPointer<PST_ExObjList> exObjPtr(new PST_ExObjList(m_srcData, stVar));

		}
			break;
		case RT_Environment:
		{
			QSharedPointer<PST_Environment> envPtr(new PST_Environment(m_srcData, stVar));
			envmentList.append(envPtr);
		}
			break;
		case RT_DrawingGroup:
		{
			QSharedPointer<PST_PPDrawingGroup> dwingGroupPtr(new PST_PPDrawingGroup(m_srcData, stVar));
			ppdwGroupList.append(dwingGroupPtr);
		}
			break;
		case RT_SlideListWithText:
		{
			QSharedPointer<PST_SlideListWithText> slideListWithTextPtr(new PST_SlideListWithText(m_srcData, stVar));
			slideListWithTxtList.append(slideListWithTextPtr);
		}
		break;
		case RT_List:
		{
			QSharedPointer<PST_List> pstListPtr(new PST_List(m_srcData, stVar));
			PSTList.append(pstListPtr);
		}
		break;
		case RT_HeadersFooters:
		{
			QSharedPointer<PST_HeadersFooters> headersFootersPtr(new PST_HeadersFooters(m_srcData, stVar));
			headersFootersList.append(headersFootersPtr);
		}
		break;
		case RT_RoundTripCustomTableStyles12Atom:
		{
			QSharedPointer<PST_RoundTripCustomTableStyles12> roundTripTableStylePtr(new PST_RoundTripCustomTableStyles12(m_srcData, stVar));
			roundTripTableStyleList.append(roundTripTableStylePtr);
		}
			break;
		case RT_EndDocumentAtom:
		{
			endDocumentAtom = QSharedPointer<PST_EndDocumentAtom>::create(m_srcData,stVar);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_Document::clearParserData()
{
	documentAtomPtr.clear();
	exObjListObjList.clear();
	envmentList.clear();
	ppdwGroupList.clear();
	slideListWithTxtList.clear();
	PSTList.clear();
	headersFootersList.clear();
	roundTripTableStyleList.clear();
	endDocumentAtom.clear();
}
