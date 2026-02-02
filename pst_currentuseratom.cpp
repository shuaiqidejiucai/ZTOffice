#include "pst_currentuseratom.h"


PST_CurrentUserAtom::PST_CurrentUserAtom(const QByteArray &byteArry, const ST_Variable& var)
	:PST_Base(byteArry, var)
{

}

int PST_CurrentUserAtom::parser()
{
	//TODO:用户数据暂时无用不解
	return Error_TODO;
}

void PST_CurrentUserAtom::clearParserData()
{
}
