#include "pst_progbinarytag.h"
#include "pstsearch.h"
PST_ProgBinaryTag::PST_ProgBinaryTag(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_ProgBinaryTag::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}
		switch (ST_TP(stVar))
		{
		case RT_CString:
		{
			ctring = QSharedPointer<PST_CString>::create(m_srcData, stVar);
			addChildNodePtr(ctring);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, ctring);
		}
		break;
		case RT_BinaryTagDataBlob:
		{
			binTagData = QSharedPointer<PST_BinaryTagData>::create(m_srcData, stVar);
			addChildNodePtr(binTagData);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, binTagData);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_ProgBinaryTag::clearParserData()
{
	ctring.clear();
	binTagData.clear();
}

int PST_ProgBinaryTag::priority()
{
	return 0;
}
