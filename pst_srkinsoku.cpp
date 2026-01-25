#include "pst_srkinsoku.h"
PST_KinsokuAtom::PST_KinsokuAtom(const QByteArray& srcData) :PST_Base(srcData)
{

}

int PST_KinsokuAtom::parser()
{
	return 0;
}

PST_SrKinsoku::PST_SrKinsoku(const QByteArray& srcData):PST_Base(srcData)
{

}

int PST_SrKinsoku::parser()
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
		case RT_KinsokuAtom:
		{
			QSharedPointer<PST_KinsokuAtom> srKinsoKuAtomPtr(new PST_KinsokuAtom(m_srcData));
			srKinsoKuAtomPtr->setSTVar(stVar);
			kinsokuAtmoList.append(srKinsoKuAtomPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return 0;
}


