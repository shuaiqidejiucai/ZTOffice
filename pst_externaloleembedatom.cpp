#include "pst_externaloleembedatom.h"

PST_ExternalOleEmbedAtom::PST_ExternalOleEmbedAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_ExternalOleEmbedAtom::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	return Error_SuccessType;
}

void PST_ExternalOleEmbedAtom::clearParserData()
{
}

int PST_ExternalOleEmbedAtom::priority()
{
	return 0;
}
