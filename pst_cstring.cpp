#include "pst_cstring.h"

PST_CString::PST_CString(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_CString::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	return 0;
}
