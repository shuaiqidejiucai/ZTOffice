#include "pst_slidetime10atom.h"

PST_SlideTime10Atom::PST_SlideTime10Atom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_SlideTime10Atom::parser()
{
	return 0;
}
