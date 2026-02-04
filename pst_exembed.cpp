#include "pst_exembed.h"
#include "pstsearch.h"
PST_ExEmbed::PST_ExEmbed(const QByteArray &srcData, const ST_Variable& var) 
	: PST_Base(srcData,var)
{
	
}


int PST_ExEmbed::parser(PSTSearch* pSearchPtr)
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
		case RT_ExternalOleEmbedAtom:
		{
			exOleEmbedAtom = QSharedPointer<PST_ExternalOleEmbedAtom>::create(m_srcData, stVar);
			addChildNodePtr(exOleEmbedAtom);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, exOleEmbedAtom);
		}
		break;
		case RT_ExternalOleObjectAtom:
		{
			exOleObjAtom = QSharedPointer<PST_ExternalOleObjectAtom>::create(m_srcData, stVar);
			addChildNodePtr(exOleObjAtom);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, exOleObjAtom);
		}
		break;
		case RT_CString:
		{
			QSharedPointer<PST_CString> cString(new PST_CString(m_srcData, stVar));
			cstringList.append(cString);
			addChildNodePtr(cString);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, cString);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_ExEmbed::clearParserData()
{
	exOleEmbedAtom.clear();
	exOleObjAtom.clear();
	cstringList.clear();
}

int PST_ExEmbed::priority()
{
	return 0;
}
