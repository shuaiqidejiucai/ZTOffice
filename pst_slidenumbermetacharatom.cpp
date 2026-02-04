#include "pst_slidenumbermetacharatom.h"

PST_SlideNumberMetaCharAtom::PST_SlideNumberMetaCharAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_SlideNumberMetaCharAtom::parser(PSTSearch* pSearchPtr)
{
	return Error_TODO;
}

void PST_SlideNumberMetaCharAtom::clearParserData()
{

}

int PST_SlideNumberMetaCharAtom::priority()
{
	return 0;
}
