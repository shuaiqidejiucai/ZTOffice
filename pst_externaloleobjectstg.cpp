#include "pst_externaloleobjectstg.h"

PST_ExternaloleObjectStg::PST_ExternaloleObjectStg(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ExternaloleObjectStg::parser()
{
	return 0;
}
