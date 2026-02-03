#include "pst_externaloleobjectstgatom.h"

PST_ExternalOleObjectStgAtom::PST_ExternalOleObjectStgAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_ExternalOleObjectStgAtom::parser()
{
	return Error_TODO;
}

void PST_ExternalOleObjectStgAtom::clearParserData()
{
}

int PST_ExternalOleObjectStgAtom::priority()
{
	return 0;
}
