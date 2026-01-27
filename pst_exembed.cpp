#include "pst_exembed.h"

PST_ExEmbed::PST_ExEmbed(const QByteArray &srcData, const ST_Variable& var) 
	: PST_Base(srcData,var)
{
	
}


int PST_ExEmbed::parser()
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
		case RT_ExternalOleEmbedAtom:
		{
			exOleEmbedAtom = QSharedPointer<PST_ExternalOleEmbedAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_ExternalOleObjectAtom:
		{
			exOleObjAtom = QSharedPointer<PST_ExternalOleObjectAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_CString:
		{
			QSharedPointer<PST_CString> cString(new PST_CString(m_srcData, stVar));
			cstringList.append(cString);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}