#include "pst_normalviewsetinfo.h"

PST_NormalViewSetInfo::PST_NormalViewSetInfo(const QByteArray& srcData):PST_Base(srcData) {}

int PST_NormalViewSetInfo::parser()
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
		case RT_NormalViewSetInfo9Atom:
		{
			QSharedPointer<PST_NormalViewSetInfo9Atom> normalViewSetInfoAtom(new PST_NormalViewSetInfo9Atom(m_srcData));
			normalViewSetInfoAtom->setSTVar(stVar);
			normalViewSetInfo9AtomList.append(normalViewSetInfoAtom);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    
    return 0;
}

PST_NormalViewSetInfo9Atom::PST_NormalViewSetInfo9Atom(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_NormalViewSetInfo9Atom::parser()
{
	return 0;
}
