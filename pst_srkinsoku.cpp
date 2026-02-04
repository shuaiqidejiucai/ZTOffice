#include "pst_srkinsoku.h"
#include "pstsearch.h"
PST_KinsokuAtom::PST_KinsokuAtom(const QByteArray& srcData, const ST_Variable& var) 
	:PST_Base(srcData, var)
{

}

int PST_KinsokuAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_KinsokuAtom::clearParserData()
{
}

int PST_KinsokuAtom::priority()
{
	return 0;
}

PST_SrKinsoku::PST_SrKinsoku(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_SrKinsoku::parser(PSTSearch* pSearchPtr)
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
		case RT_KinsokuAtom:
		{
			QSharedPointer<PST_KinsokuAtom> srKinsoKuAtomPtr(new PST_KinsokuAtom(m_srcData, stVar));
			kinsokuAtmoList.append(srKinsoKuAtomPtr);
			addChildNodePtr(srKinsoKuAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, srKinsoKuAtomPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return Error_SuccessType;
}

void PST_SrKinsoku::clearParserData()
{
	kinsokuAtmoList.clear();
}

int PST_SrKinsoku::priority()
{
	return 0;
}


