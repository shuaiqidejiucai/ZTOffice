#include "pst_mainmaster.h"

PST_MainMaster::PST_MainMaster(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_MainMaster::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(stVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return -1;
		}
		switch (ST_TP(stVar))
		{
		case RT_SlideAtom:
		{
			slideAtomPtr = QSharedPointer<PST_SlideAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_ColorSchemeAtom:
		{
			QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtom(new PST_ColorSchemeAtom(m_srcData, stVar));
			colorSchemeAtomPtrList.append(colorSchemeAtom);
		}
		break;
		case RT_TextMasterStyleAtom:
		{
			QSharedPointer<PST_TxMasterStyleAtom> txMasterStyleAtomPtr(new PST_TxMasterStyleAtom(m_srcData, stVar));
			txMasterStyleAtomPtrList.append(txMasterStyleAtomPtr);
		}
			break;
		default:
			break;
			pos = ST_EP(stVar);
		}
	} while (pos < ST_EP(stVar));
	return 0;
}
