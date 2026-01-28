#include "pst_slideatom.h"

PST_SlideAtom::PST_SlideAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_SlideAtom::parser()
{
	return 0;
}
