#include "pst_progtags.h"

PST_ProgTags::PST_ProgTags(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_ProgTags::parser()
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
		case RT_ProgBinaryTag:
		{
			QSharedPointer<PST_ProgBinaryTag> progBinTagPtr (new PST_ProgBinaryTag(m_srcData, stVar));
			progBinTagList.append(progBinTagPtr);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
