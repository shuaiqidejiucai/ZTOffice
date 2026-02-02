#include "pst_slidenumbermetacharatom.h"

PST_SlideNumberMetaCharAtom::PST_SlideNumberMetaCharAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_SlideNumberMetaCharAtom::parser()
{
	return Error_TODO;
}

void PST_SlideNumberMetaCharAtom::clearParserData()
{

}
