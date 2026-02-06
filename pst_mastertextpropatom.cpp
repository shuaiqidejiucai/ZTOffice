#include "pst_mastertextpropatom.h"

PST_MasterTextPropAtom::PST_MasterTextPropAtom(const QByteArray& srcData, const ST_Variable& var) 
:PST_Base(srcData, var){}

int PST_MasterTextPropAtom::parser(PSTSearch* pSearchPtr)
{
	return 0;
}

void PST_MasterTextPropAtom::clearParserData()
{
}

int PST_MasterTextPropAtom::priority()
{
	return 0;
}
