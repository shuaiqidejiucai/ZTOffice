#include "pstsearch.h"

PSTSearch::PSTSearch() {}

bool PSTSearch::insertRecordMap(quint32 key, const QWeakPointer<PST_Base>& value)
{
    if (m_posVPSTBaseMap.contains(key))
    {
        //TODO:加警告日志，已存在key证明文件解析出问题了
        return false;
    }
    return true;
}
