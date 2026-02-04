#include "pst_normalviewsetinfo.h"
#include "pstsearch.h"
PST_NormalViewSetInfo::PST_NormalViewSetInfo(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_NormalViewSetInfo::parser(PSTSearch* pSearchPtr)
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
		case RT_NormalViewSetInfo9Atom:
		{
			QSharedPointer<PST_NormalViewSetInfo9Atom> normalViewSetInfoAtom(new PST_NormalViewSetInfo9Atom(m_srcData, stVar));
			normalViewSetInfo9AtomList.append(normalViewSetInfoAtom);
			addChildNodePtr(normalViewSetInfoAtom);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, normalViewSetInfoAtom);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    
    return Error_SuccessType;
}

void PST_NormalViewSetInfo::clearParserData()
{
	normalViewSetInfo9AtomList.clear();
}

int PST_NormalViewSetInfo::priority()
{
	return 0;
}

PST_NormalViewSetInfo9Atom::PST_NormalViewSetInfo9Atom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_NormalViewSetInfo9Atom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_NormalViewSetInfo9Atom::clearParserData()
{
}

int PST_NormalViewSetInfo9Atom::priority()
{
	return 0;
}
