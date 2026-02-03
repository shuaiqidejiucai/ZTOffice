#include "pst_cstring.h"

PST_CString::PST_CString(const QByteArray &srcData, const ST_Variable& var):PST_Base(srcData, var)
{

}

int PST_CString::parser()
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	return Error_BinType;
}

void PST_CString::clearParserData()
{
}

int PST_CString::priority()
{
	return 0;
}
