#include "pst_msofbtopt.h"

PST_MSOfbtOPT::PST_MSOfbtOPT(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_MSOfbtOPT::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	quint16 num = ST_RI(m_STVar);

	QList<quint32> sizeList;
	//Fopte
	for (quint16 i = 0; i < num; ++i)
	{
		ST_SP(stVar) = pos;
		pos += 6;
		ST_EP(stVar) = pos;
		QSharedPointer<Fopte> foptePtr(new Fopte(m_srcData, stVar));
		foptePtr->parser();
		if (foptePtr->fComplex == 1)
		{
			sizeList.append(foptePtr->op);
		}
		fopteList.append(foptePtr);
	}
	//FOPTEComplex
	ST_Variable stVar2;
	for (quint16 i = 0; i < sizeList.count(); ++i)
	{
		if (pos >= ST_EP(m_STVar))
		{
			break;
		}
		quint32 opSize = sizeList.at(i);
		ST_SP(stVar2) = pos;
		pos += opSize;
		ST_EP(stVar2) = pos;
		QSharedPointer<FOPTEComplex> foptePtr(new FOPTEComplex(m_srcData,stVar));
		fopteComList.append(foptePtr);
	}
	return 0;
}
