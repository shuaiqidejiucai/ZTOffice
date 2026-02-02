#include "pst_fontcollection.h"
PST_FontEntityAtom::PST_FontEntityAtom(const QByteArray& srcData, const ST_Variable& var) :PST_Base(srcData, var)
{

}

int PST_FontEntityAtom::parser()
{
	return Error_TODO;
}

void PST_FontEntityAtom::clearParserData()
{
}

PST_FontCollection::PST_FontCollection(const QByteArray& srcData, const ST_Variable& var):PST_Base(srcData,var)
{

}

int PST_FontCollection::parser()
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
		case RT_FontEntityAtom:
		{
			QSharedPointer<PST_FontEntityAtom> fontEntityAtomPtr(new PST_FontEntityAtom(m_srcData, stVar));
			fontEntityAtomList.append(fontEntityAtomPtr);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_FontCollection::clearParserData()
{
	fontEntityAtomList.clear();
}


