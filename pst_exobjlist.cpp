#include "pst_exobjlist.h"
#include "pstsearch.h"
#include "pst_externalobjectlistatom.h"
#include "pst_exembed.h"
PST_ExObjList::PST_ExObjList(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_ExObjList::parser(PSTSearch* pSearchPtr)
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
		case RT_ExternalObjectListAtom:
		{
			exObjListAtomPtr = QSharedPointer<PST_ExternalObjectListAtom>::create(m_srcData, stVar);
			addChildNodePtr(exObjListAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, exObjListAtomPtr);
		}
		break;
		case RT_ExternalOleEmbed:
		{
			QSharedPointer<PST_ExEmbed> exEmbed(new PST_ExEmbed(m_srcData, stVar));
			exembedList.append(exEmbed);
			addChildNodePtr(exEmbed);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, exEmbed);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_ExObjList::clearParserData()
{
	exObjListAtomPtr.clear();
	exembedList.clear();
}

int PST_ExObjList::priority()
{
	return 0;
}
