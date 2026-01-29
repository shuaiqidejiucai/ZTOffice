#include "officeartspcontainer.h"

OfficeArtSpContainer::OfficeArtSpContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int OfficeArtSpContainer::parser()
{
	return 0;
}
