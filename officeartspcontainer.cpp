#include "officeartspcontainer.h"

OfficeArtSpContainer::OfficeArtSpContainer(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int OfficeArtSpContainer::parser()
{
	//TODO:测试简单文档没碰到
	return Error_TODO;
}

void OfficeArtSpContainer::clearParserData()
{
}
