#include "pst_slidelistwithtext.h"
#include "pstsearch.h"
PST_SlideListWithText::PST_SlideListWithText(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_SlideListWithText::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}

		if (ST_TP(stVar) == RT_SlidePersistAtom)
		{
			QSharedPointer<PST_SlidePersistAtom> slidePersistAtom (new PST_SlidePersistAtom(m_srcData,stVar));
			slidePerAtomList.append(slidePersistAtom);
			addChildNodePtr(slidePersistAtom);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, slidePersistAtom);
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_SlideListWithText::clearParserData()
{
	slidePerAtomList.clear();
}

int PST_SlideListWithText::priority()
{
	return 0;
}
