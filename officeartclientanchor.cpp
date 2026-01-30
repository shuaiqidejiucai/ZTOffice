#include "officeartclientanchor.h"

OfficeArtClientAnchor::OfficeArtClientAnchor(const QByteArray& srcData, const ST_Variable& var)
:PST_Base(srcData, var){}

int OfficeArtClientAnchor::parser()
{
    if (m_isParser)
    {
        clearParserData();
    }
    
    m_isParser = true;
    quint32 pos = ST_SP(m_STVar);
    
    if (ST_SZ(m_STVar) == 0x8)
    {
        stRectStructPtr = QSharedPointer<ST_RectStruct>::create(ST_RectStruct::Small);
        stRectStructPtr->anchoData.smallRect.top = GetFlagData<qint16>(m_srcData, pos);
        stRectStructPtr->anchoData.smallRect.left = GetFlagData<qint16>(m_srcData, pos);
        stRectStructPtr->anchoData.smallRect.right = GetFlagData<qint16>(m_srcData, pos);
        stRectStructPtr->anchoData.smallRect.bottom = GetFlagData<qint16>(m_srcData, pos);
    }
    else if (ST_SZ(m_STVar) == 0x10)
    {
        stRectStructPtr = QSharedPointer<ST_RectStruct>::create(ST_RectStruct::Big);
        stRectStructPtr->anchoData.bigRect.top = GetFlagData<qint32>(m_srcData, pos);
        stRectStructPtr->anchoData.bigRect.left = GetFlagData<qint32>(m_srcData, pos);
        stRectStructPtr->anchoData.bigRect.right = GetFlagData<qint32>(m_srcData, pos);
        stRectStructPtr->anchoData.bigRect.bottom = GetFlagData<qint32>(m_srcData, pos);
    }
    else
    {

    }
    return Error_SuccessType;
}

void OfficeArtClientAnchor::clearParserData()
{
    m_isParser = false;
    stRectStructPtr.clear();
}
