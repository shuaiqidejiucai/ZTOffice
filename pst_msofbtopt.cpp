#include "pst_msofbtopt.h"

PST_MSOfbtOPT::PST_MSOfbtOPT(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_MSOfbtOPT::parser()
{
	ST_Variable stVarA;
	quint32 pos = ST_OP(m_STVar);
	physicalStruct(pos, m_srcData, stVarA);
	pos = ST_SP(stVarA);
	quint16 num = ST_RI(stVarA);
	ST_Variable stVar;
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
	return Error_SuccessType;
}

void PST_MSOfbtOPT::clearParserData()
{
	fopteList.clear();
	fopteComList.clear();
}

int PST_MSOfbtOPT::priority()
{
	return 0;
}
