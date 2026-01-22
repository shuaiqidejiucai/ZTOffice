#include "pst_document.h"
#include "zttools.h"
PST_Document::PST_Document(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_Document::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return -1;
		}
		switch (ST_TP(stVar))
		{
		case RT_DocumentAtom:
		{
			documentAtomPtr = QSharedPointer<PST_DocumentAtom>::create(m_srcData);
			documentAtomPtr->setSTVar(stVar);
		}
			break;
		case RT_ExternalObjectList:
		{
			QSharedPointer<PST_ExObjList> exObjPtr(new PST_ExObjList(m_srcData));
			exObjPtr->setSTVar(stVar);

		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
		

	if (isFind)
	{
		quint32 startPos = ST_SP(stVar);
		qint32 slideSizeX = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		qint32 slideSizeY = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		qint32 notesSizeX = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		qint32 notesSizeY = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		qint32 numer = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));//分子
		startPos += 4;
		qint32 denom = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));//分母
		startPos += 4;
		quint32 notesMasterPersistIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 handoutMasterPersistIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint16 firstSlideNumber = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 2;
		quint16 slideSizeType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 2;
		quint8 fSaveWithFonts = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));//是否为嵌入式字体
		startPos += 1;
		//标题幻灯片上的“占位符形状”是否不显示
		quint8 fOmitTitlePlace = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		//是否为从右向左的文档
		quint8 fRightToLeft = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		//是否显示批注评论
		quint8 fShowComments = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		return ST_EP(stVar);
	}
	return 0;
}
