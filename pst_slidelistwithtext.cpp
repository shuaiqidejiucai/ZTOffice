#include "pst_slidelistwithtext.h"

PST_SlideListWithText::PST_SlideListWithText(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_SlideListWithText::parser()
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

		if (ST_TP(stVar) == RT_SlidePersistAtom)
		{
			QSharedPointer<PST_SlidePersistAtom> slidePersistAtom (new PST_SlidePersistAtom(m_srcData,stVar));
			slidePerAtomList.append(slidePersistAtom);
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
