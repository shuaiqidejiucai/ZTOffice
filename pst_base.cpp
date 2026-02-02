#include "pst_base.h"

PST_Base::PST_Base(const QByteArray& srcData, const ST_Variable& var):m_STVar(var), m_srcData(srcData), m_isParser(false){}

QSharedPointer<PST_Base> PST_Base::CreateOfficeClassByType(const QByteArray& srcData, const ST_Variable& var)
{
	return QSharedPointer<PST_Base>();
}

int PST_Base::parserData()
{
	if (m_isParser)
	{
		clearData();
	}
	m_isParser = true;
	return parser();
}

void PST_Base::clearData()
{
	m_isParser = false;
	clearParserData();
}
