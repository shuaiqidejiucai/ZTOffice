#include "pst_externaloleembedatom.h"

PST_ExternalOleEmbedAtom::PST_ExternalOleEmbedAtom(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_ExternalOleEmbedAtom::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	return 0;
}
