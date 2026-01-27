#include "pst_documentatom.h"
#include "zttools.h"
PST_DocumentAtom::PST_DocumentAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_DocumentAtom::parser()
{
	quint32 pos = m_STVar.startPos;
	SlideSize.x = GetFlagData<qint32>(m_srcData, pos);
	SlideSize.y = GetFlagData<qint32>(m_srcData, pos);
	NotesSize.x = GetFlagData<qint32>(m_srcData, pos);
	NotesSize.y = GetFlagData<qint32>(m_srcData, pos);
	ServerZoom.numer = GetFlagData<qint32>(m_srcData, pos); //分子
	ServerZoom.denom = GetFlagData<qint32>(m_srcData, pos);//分母

	notesMasterPersistIdRef = GetFlagData<quint32>(m_srcData, pos);
	handoutsMasterPersistIdRef = GetFlagData<quint32>(m_srcData, pos);
	firstSlideNumber = GetFlagData<quint16>(m_srcData, pos);
	slideSizeType = GetFlagData<quint16>(m_srcData, pos);
	fSaveWithFonts = GetFlagData<quint8>(m_srcData, pos);//是否为嵌入式字体
	//标题幻灯片上的“占位符形状”是否不显示
	fOmitTitlePlace = GetFlagData<quint8>(m_srcData, pos);
	//是否为从右向左的文档
	fRightToLeft = GetFlagData<quint8>(m_srcData, pos);
	//是否显示批注评论
	fShowComments = GetFlagData<quint8>(m_srcData, pos);
	return 0;
}
