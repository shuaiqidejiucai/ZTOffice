#include "pst_base.h"

PST_Base::PST_Base(const QByteArray& srcData, const ST_Variable& var):m_STVar(var), m_srcData(srcData), m_isParser(false){}

int PST_Base::parserData()
{
	if (m_isParser)
	{
		clearData();
	}
	return parser();
}

void PST_Base::clearData()
{
	m_isParser = false;
	clearParserData();
}
