#include "pst_progbinarytag.h"

PST_ProgBinaryTag::PST_ProgBinaryTag(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_ProgBinaryTag::parser()
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
		case RT_CString:
		{
			ctring = QSharedPointer<PST_CString>::create(m_srcData, stVar);
		}
		break;
		case RT_BinaryTagDataBlob:
		{
			binTagData = QSharedPointer<PST_BinaryTagData>::create(m_srcData, stVar);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
