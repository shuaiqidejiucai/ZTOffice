#include "pst_headersfooters.h"

PST_HeadersFooters::PST_HeadersFooters(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_HeadersFooters::parser()
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
		case RT_HeadersFootersAtom:
		{
			headersFootersAtom = QSharedPointer<PST_HeadsFootersAtom>::create(m_srcData, stVar);
			addChildNodePtr(headersFootersAtom);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}

void PST_HeadersFooters::clearParserData()
{
	headersFootersAtom.clear();
}

int PST_HeadersFooters::priority()
{
	return 0;
}

PST_HeadsFootersAtom::PST_HeadsFootersAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_HeadsFootersAtom::parser()
{
	return Error_TODO;
}

void PST_HeadsFootersAtom::clearParserData()
{
}

int PST_HeadsFootersAtom::priority()
{
	return 0;
}
