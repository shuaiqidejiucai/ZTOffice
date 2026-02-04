#include "pst_externaloleobjectatom.h"

PST_ExternalOleObjectAtom::PST_ExternalOleObjectAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_ExternalOleObjectAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_ExternalOleObjectAtom::clearParserData()
{
}

int PST_ExternalOleObjectAtom::priority()
{
	return 0;
}
