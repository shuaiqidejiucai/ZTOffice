#include "ztwppdocument.h"
#include <qdir.h>
#include <qmath.h>
#include <qtemporaryfile.h>
#include <qdebug.h>
using namespace ZT_Libolecf;
ZTWPPDocument::ZTWPPDocument() {}

QString GetQString(const char * dataPtr, quint32 length)
{
	QTextDecoder* decoder = QTextCodec::codecForName("UTF-16LE")->makeDecoder();
	QString qsContent = decoder->toUnicode(dataPtr, length);
	delete decoder;
	//移除终止符（如果有）
	if (qsContent.endsWith(QChar::Null)) {
		qsContent.chop(1);
	}
	return qsContent;
}

bool ZTWPPDocument::openWPPFile(const QString& qsFilePath)
{
	QString nativePath = QDir::toNativeSeparators(qsFilePath);
	QSharedPointer<libolecf_error_t> error;
	int errorCode = ZT_libolecf_file_initialize(m_oleFilePtr, &error);
	if (errorCode == 1 && m_oleFilePtr)
	{
		errorCode = ZT_libolecf_file_open(m_oleFilePtr, nativePath.toUtf8().constData(), LIBOLECF_OPEN_READ, &error);
		if (errorCode == 1)
		{
			ZT_libolecf_file_get_root_item(m_oleFilePtr, m_pRootIemPtr, nullptr);
			return true;
		}
	}
	return false;
}

bool ZTWPPDocument::readPPTData()
{
	QSharedPointer<libolecf_item_t> powerPointItemPtr;
	bool isFind = ZTTools::findOleTreeItem(m_pRootIemPtr, "PowerPoint Document", powerPointItemPtr, true, true);
	if (isFind && powerPointItemPtr)
	{
		m_srcData = ZTTools::getOleItemData(powerPointItemPtr);
	}
	return false;
}

void ZTWPPDocument::parserData()
{
	ST_Variable stVar;
	quint32 pos = 0;
	bool isValid;

	do
	{
		isValid = physicalStruct(pos, stVar);
		if (isValid)
		{
			m_typeOffsetList.append(QPair<quint16, quint32>(ST_TP(stVar), pos));
		}
		pos = ST_EP(stVar);
	} while (isValid);

	parserDocument();
}

bool ZTWPPDocument::physicalStruct(quint32 pos, ST_Variable& stVar)
{
	if (pos + 8 < m_srcData.size())
	{
		quint16 head = GetFlagData<quint16>(m_srcData.constData(), pos);
		ST_TP(stVar) = GetFlagData<quint16>(m_srcData.constData(), pos);
		ST_SZ(stVar) = GetFlagData<quint32>(m_srcData.constData(), pos);
		
		ST_RV(stVar) = head & 0xF;
		ST_RI(stVar) = head >> 4;
		if (pos + ST_SZ(stVar) < m_srcData.size())
		{
			ST_SP(stVar) = pos;
			ST_EP(stVar) = pos + ST_SZ(stVar);
			return true;
		}
	}
	return false;
}

quint16 ZTWPPDocument::getPhysicalStructType(quint32 pos)
{
	if (pos + 8 < m_srcData.size())
	{
		pos += 2;
		quint16 ftType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		return ftType;
	}
	return 0;
}

QList<QPair<quint16, quint32>> ZTWPPDocument::findType(HeaderType headType)
{
	QList<QPair<quint16, quint32>> tmpList;
	for (const QPair<quint16, quint32>& tmpPair : m_typeOffsetList)
	{
		if (tmpPair.first == headType)
		{
			tmpList.append(tmpPair);
		}
	}
	return tmpList;
}

bool ZTWPPDocument::oleAttachmentSecondParser(const QString& qsFilePath, ST_VarantFile& varantFile)
{
	QString nativePath = QDir::toNativeSeparators(qsFilePath);
	QSharedPointer<libolecf_error_t> error;
	QSharedPointer<libolecf_file_t> oleFilePtr;
	int errorCode = ZT_libolecf_file_initialize(oleFilePtr, &error);
	if (errorCode == 1 && oleFilePtr)
	{
		errorCode = ZT_libolecf_file_open(oleFilePtr, nativePath.toUtf8().constData(), LIBOLECF_OPEN_READ, &error);
		if (errorCode == 1)
		{
			QSharedPointer<libolecf_item_t> rootIemPtr;
			ZT_libolecf_file_get_root_item(oleFilePtr, rootIemPtr, nullptr);
			bool isOutPut = false;
			QSharedPointer<libolecf_item_t> resultIemPtr;
			EU_DocumentType docType = ZTTools::getOleFileFormat(rootIemPtr, isOutPut, resultIemPtr);
			if (docType == EU_DocumentType::EU_BinType)
			{
				if (isOutPut && resultIemPtr)
				{
					QByteArray data = ZTTools::getOleItemData(resultIemPtr);
					ZTTools::parseOle10Native(data, varantFile);
				}
			}
			else if(docType == EU_DocumentType::EU_DOCType)
			{
				varantFile.qsSuffix = ".doc";
				varantFile.fileData = ZTTools::getOleItemData(rootIemPtr);
			}
			else if (docType == EU_DocumentType::EU_PPTType)
			{
				varantFile.qsSuffix = ".ppt";
				varantFile.fileData = ZTTools::getOleItemData(rootIemPtr);
			}
			else if (docType == EU_DocumentType::EU_XLSType)
			{
				varantFile.qsSuffix = ".xls";
				varantFile.fileData = ZTTools::getOleItemData(rootIemPtr);
			}
			else if (docType == EU_DocumentType::EU_DOCXType)
			{
				varantFile.qsSuffix = ".docx";
				if (isOutPut && resultIemPtr)
				{
					varantFile.fileData = ZTTools::getOleItemData(resultIemPtr);
				}
			}
			else if (docType == EU_DocumentType::EU_PPTXType)
			{
				varantFile.qsSuffix = ".pptx";
				if (isOutPut && resultIemPtr)
				{
					varantFile.fileData = ZTTools::getOleItemData(resultIemPtr);
				}
			}
			else if (docType == EU_DocumentType::EU_XLSXType)
			{
				varantFile.qsSuffix = ".xlsx";
				if (isOutPut && resultIemPtr)
				{
					varantFile.fileData = ZTTools::getOleItemData(resultIemPtr);
				}
			}
			else
			{
				varantFile.fileData = ZTTools::getOleItemData(rootIemPtr);
			}
			return true;
		}
	}
	return false;
}

bool ZTWPPDocument::oleAttachmentSecondParser(const QByteArray& oleData)
{
	return false;
}

//quint64 ZTWPPDocument::getOffsetTypeID(quint32 offset, quint16 type)
//{
//    quint64 offsetID = static_cast<quint64>(offset) << 16;
//    offsetID |= type;
//    return offsetID;
//}
//
//quint32 ZTWPPDocument::getType(quint64 offsetID)
//{
//    quint16 type = offsetID & 0xFFFF;
//    return type;
//}
//
//quint32 ZTWPPDocument::getOffset(quint64 offsetID)
//{
//    quint32 offset = static_cast<quint32>(offsetID >> 16);
//    return offset;
//}


quint32 ZTWPPDocument::parserDocument()
{
	ST_Variable stVar;
	bool isValid = false;
	bool isFind = false;
	QList<QPair<quint16, quint32> > documentList = findType(RT_Document);
	/*std::function<quint32(quint32)> func = std::bind(&ZTWPPDocument::parserExObjList, this, std::placeholders::_1);*/
	for (const QPair<quint16, quint32>& tmpPair : documentList)
	{
		isFind = true;
		isValid = physicalStruct(tmpPair.second, stVar);
		if (isValid)
		{
			quint32 tmpPos = parserDocumentAtom(ST_SP(stVar));
			ST_Variable stVar2;
			bool isValid2 = false;
			do
			{
				isValid2 = physicalStruct(tmpPos, stVar2);
				if (!isValid2)
				{
					break;
				}
				switch (ST_TP(stVar2))
				{
				case RT_ExternalObjectList: {
					tmpPos = parserExObjList(tmpPos);
				}
					break;
				case RT_Environment: {
					tmpPos = parserDocumentTextInfoContainer(tmpPos);
				}
					break;
				case RT_SoundCollection: {
					tmpPos = parserSoundCollection(tmpPos);
				}
					break;
				case RT_DrawingGroup:
					tmpPos = parserDrawingGroup(tmpPos);
					break;
				case RT_SlideListWithText:{
					if (ST_RI(stVar2) == 0x001)
					{
						tmpPos = parserMasterList(tmpPos);
					}
					else if (ST_RI(stVar2) == 0x000)
					{
						tmpPos = parserSlideList(tmpPos);
					}
					else if (ST_RI(stVar2) == 0x002)
					{
						tmpPos = parserNotesList(tmpPos);
					}
					else
					{
						tmpPos = ST_EP(stVar2);
					}
				}
					break;
				case RT_List: {
					tmpPos = parserDocInfoList(tmpPos);
				}
					break;
				case RT_HeadersFooters: {
					if (ST_RI(stVar2) == 0x000)
					{
						tmpPos = ST_EP(stVar2);
						//tmpPos = parserPerSlideHeadersFootersContainer(tmpPos);
					}
					else if (ST_RI(stVar2) == 0x003)
					{
						tmpPos = parserSlideHF(tmpPos);
					}
					else if (ST_RI(stVar2) == 0x004)
					{
						tmpPos = parserNotesHF(tmpPos);
					}
					else
					{
						tmpPos = ST_EP(stVar2);
					}
				}
					break;
				case RT_SlideShowDocInfoAtom: {
					tmpPos = parserSlideShowDocInfoAtom(tmpPos);
				}
					break;
				case RT_NamedShows: {
					tmpPos = parserNamedShows(tmpPos);
				}
					break;
				case RT_Summary: {
					tmpPos = parserSummary(tmpPos);
				}
					break;
				case RT_DocRoutingSlipAtom: {
					tmpPos = parserDocRoutingSlipAtom(tmpPos);
				}
					break;
				case RT_PrintOptionsAtom:{
					tmpPos = parserPrintOptionsAtom(tmpPos);
				}
					break;
				default: {
					tmpPos = ST_EP(stVar2);
				}
					break;
				}
			} while (tmpPos < ST_EP(stVar));
		}
	}

	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserDocumentAtom(quint32 pos)
{
	ST_Variable stVar;
	bool isValid = false;
	bool isFind = false;
	quint32 srcPos = pos;
	do
	{
		isValid = physicalStruct(pos, stVar);
		if (isValid && ST_TP(stVar) == RT_DocumentAtom)
		{
			isFind = true;
			break;
		}
	} while (false);

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
	return srcPos;
}

quint32 ZTWPPDocument::parserExObjList(quint32 pos)
{
	ST_Variable stVar;

	bool isValid = false;

	bool isFind = false;
	do
	{
		isValid = physicalStruct(pos, stVar);
		if (isValid && ST_TP(stVar) == RT_ExternalObjectList)
		{
			isFind = true;
			break;
		}
	} while (false);

	if (isFind)
	{
		quint32 exObj = 0;
		quint32 tmpPos = parserExObjListAtom(ST_SP(stVar));
		if (ST_SZ(stVar) - 12 > 0)//有容器
		{
			parserExObjListSubContainer(tmpPos);
		}
		return ST_EP(stVar);
	}
	return pos;
}

quint32 ZTWPPDocument::parserExObjListAtom(quint32 pos)
{
	ST_Variable stVar;
	quint32 srcPos = pos;
	bool isValid = false;

	bool isFind = false;
	do
	{
		isValid = physicalStruct(pos, stVar);
		if (isValid && ST_TP(stVar) == RT_ExternalObjectListAtom)
		{
			isFind = true;
			break;
		}
	} while (false);

	if (isFind)
	{
		qint32 exObjIdSeed = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + ST_SP(stVar)));
		pos += 4;
		return ST_EP(stVar);
	}
	return srcPos;
}

void ZTWPPDocument::parserExObjListSubContainer(quint32 pos)
{
	ST_Variable stVar;
	bool isValid = false;

	bool isFind = false;

	QList<HeaderType> subContainerList;
	subContainerList.append(RT_ExternalAviMovie);
	subContainerList.append(RT_ExternalCdAudio);
	subContainerList.append(RT_ExternalOleControl);
	subContainerList.append(RT_ExternalHyperlink);
	subContainerList.append(RT_ExternalMciMovie);
	subContainerList.append(RT_ExternalMidiAudio);
	subContainerList.append(RT_ExternalOleEmbed);
	subContainerList.append(RT_ExternalOleLink);
	subContainerList.append(RT_ExternalWavAudioEmbedded);
	subContainerList.append(RT_ExternalWavAudioLink);

	int clac = 0;
	do
	{
		clac++;
		isValid = physicalStruct(pos, stVar);
		if (isValid && subContainerList.contains((HeaderType)ST_TP(stVar) ))
		{
			isFind = true;
			switch (ST_TP(stVar))
			{
			case RT_ExternalAviMovie:
				break;
			case RT_ExternalCdAudio:
				break;
			case RT_ExternalOleControl:
				break;
			case RT_ExternalHyperlink:
				break;
			case RT_ExternalMciMovie:
				break;
			case RT_ExternalMidiAudio:
				break;
			case RT_ExternalOleEmbed:{
				parserExOleEmbedContainer(ST_SP(stVar));
			}
				break;
			case RT_ExternalOleLink:
				break;
			case RT_ExternalWavAudioEmbedded:
				break;
			case RT_ExternalWavAudioLink:
				break;
			default:
				break;
			}
			pos += ST_SZ(stVar);
		}
		else
		{
			break;
		}
	} while (true);

	return;
}

void ZTWPPDocument::parserExOleEmbedContainer(quint32 pos)
{
	ST_Variable stVar;

	bool isValid = false;

	if (true)
	{
		//ExOleEmbedAtom
		isValid = physicalStruct(pos, stVar);
		if (!isValid || ST_TP(stVar) != RT_ExternalOleEmbedAtom)
		{
			return;
		}
		quint32 startPos = ST_SP(stVar);

		quint32 exColorFollow = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		//是否需要锁定old服务器
		quint8 fCantLockServer = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		//是否可以省略向 OLE 服务器发送对象尺寸信息
		quint8 fNoSizeToServer = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		//指定 OLE 对象是否表示由 Word.Document ProgID 创建的表格（废弃）
		quint8 fIsTable = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		quint8 OleEmbedAtomUnused = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 1;
		// ExOleObjAtom
		isValid = physicalStruct(startPos, stVar);
		if (!isValid || ST_TP(stVar) != RT_ExternalOleObjectAtom)
		{
			return;
		}
		//指定 OLE 对象用哪种"视图方面"来显示
		quint32 drawAspect = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		//嵌入类型：Embedded、Linked、Control、Embed
		quint32 type = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 exObjId = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 subType = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 persistIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		parserPersistDirectoryAtom(persistIdRef);
		startPos += 4;
		quint32 unused = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		//其余的因为是可选所以不解析
	}
}

void outputFile2(const QByteArray& data)
{
	QFile file("E:/test/newppt2.stream");
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(data);
		file.close();
	}
}

bool ZTWPPDocument::parserPersistDirectoryAtom(quint32 idRef, PersistDirectoryType type)
{
	QList<QPair<quint16, quint32>> PersistDirectoryAtomList = findType(RT_PersistDirectoryAtom);
	for (const QPair<quint16, quint32>& tmpPair : PersistDirectoryAtomList)
	{
		quint32 pos = tmpPair.second;
		quint16 ftHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 2;
		quint16 ftType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 2;
		//官方标准中没有写这块记录了size
		quint16 ftSize = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;

		quint32 PersistBits = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		quint16 cPersist = PersistBits >> 20;
		quint32 persistId = PersistBits & 0xFFFFF;
		pos += 4;
		for (quint16 i = 1; i <= cPersist; ++i)
		{
			if (i == idRef)
			{
				quint32 rgPersistOffset = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));

				if (type == AttachmentType)
				{
					extratorAttachment(rgPersistOffset);
				}
				else if(type == TextType)
				{
					extratorText(rgPersistOffset);
				}
				else if(type == ImageType)
				{

				}
				else
				{

				}
				
				break;
			}
			pos += 4;
		}
		int ssss = 0;
	}
	return false;
}

int ZTWPPDocument::extratorAttachment(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	ftHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	pos += 2;
	ftType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	pos += 2;
	ftSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	pos += 4;
	quint32 decompressedSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	pos += 4;

	QByteArray compressedData = m_srcData.mid(pos, ftSize);
	// ========== 使用 inflate 流式解压 ==========

	//数据开始
	uchar* oleDataStart = reinterpret_cast<uchar*>(m_srcData.data() + pos);

	QTemporaryFile file;
	if (file.open())
	{
		z_stream strm;
		memset(&strm, 0, sizeof(strm));
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		inflateInit(&strm);
		quint32 bufferPos = pos;
		quint32 bufferSize = 65535;
		strm.avail_in = ftSize;
		strm.next_in = oleDataStart;
		do
		{
			QByteArray outPutData(bufferSize, 0);
			strm.avail_out = bufferSize;
			strm.next_out = reinterpret_cast<Bytef*>(outPutData.data());
			if (strm.total_in + bufferSize >= ftSize)
			{
				int ret = inflate(&strm, Z_FINISH);
			}
			else
			{
				inflate(&strm, Z_NO_FLUSH);
			}

			if (strm.avail_out > 0)
			{
				outPutData.resize(bufferSize - strm.avail_out);
			}
			file.write(outPutData);

		} while (strm.total_in < ftSize);
		inflateEnd(&strm);
		file.close();
		//ST_VarantFile varFile;
		//oleAttachmentSecondParser(file.fileName(), varFile);
		//outputFile2(varFile.fileData);
	}
	return 0;
}

int ZTWPPDocument::extratorText(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	ftHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	pos += 2;
	ftType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	pos += 2;
	ftSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	//pos += 4；带上总大小给函数
	if (ftType == RT_MainMaster)
	{

	}
	else if(ftType == RT_Slide)
	{
		parserSlide(pos);
	}
	return 0;
}

//默认用什么字体、多大字号、怎么对齐属于样式层
quint32 ZTWPPDocument::parserDocumentTextInfoContainer(quint32 pos)
{
	ST_Variable stVar;

	bool isValid = false;
	//DocumentTextInfoContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_Environment)
	{
		return pos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserSoundCollection(quint32 pos)
{
	ST_Variable stVar;
	bool isValid = false;
	//ExOleEmbedAtom
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_SoundCollection)
	{
		return pos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserDrawingGroup(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//ExOleEmbedAtom
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_DrawingGroup)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserMasterList(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//MasterListWithTextContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_SlideListWithText)
	{
		return srcPos;
	}

	if (ST_RI(stVar) != 0x001)
	{
		return srcPos;
	}

	//MasterPersistAtom
	/*for (int i = 0; i < ftSize; ++i)
	{

	}*/
	

	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserDocInfoList(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//DocInfoListContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_List)
	{
		return srcPos;
	}

	do
	{
		pos = parserDocInfoListContainer(pos);
	} while (pos < ST_EP(stVar));

	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserSlideHF(quint32 pos)
{
	ST_Variable stVar;
	quint32 srcPos = pos;
	bool isValid = false;
	//SlideHeadersFootersContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_HeadersFooters)
	{
		return srcPos;
	}
	if (ST_RI(stVar) != 0x003)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserNotesHF(quint32 pos)
{
	ST_Variable stVar;
	quint32 srcPos = pos;
	bool isValid = false;
	//NotesHeadersFootersContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_HeadersFooters)
	{
		return srcPos;
	}

	if (ST_RI(stVar) != 0x004)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserSlideList(quint32 pos)
{
	ST_Variable stVar;
	quint32 srcPos = pos;
	bool isValid;
	//SlideListWithTextContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_SlideListWithText)
	{
		return srcPos;
	}
	
	if (ST_RI(stVar) != 0x000)
	{
		return srcPos;
	}
	pos = ST_SP(stVar);
	do
	{
		pos = parserSlideListWithTextSubContainerOrAtom(pos);
	} while (pos < ST_EP(stVar));

	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserSlideListWithTextSubContainerOrAtom(quint32 pos)
{
	ST_Variable stVar;
	quint32 srcPos = pos;
	bool isValid;
	//SlideListWithTextSubContainerOrAtom
	isValid = physicalStruct(pos, stVar);
	
	if (!isValid)
	{
		return srcPos;
	}
	quint32 startPos = ST_SP(stVar);
	switch (ST_TP(stVar))
	{
	case RT_SlidePersistAtom: {
		quint32 persistIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		//TODO:这里有8字节的内容现在用不到不解析
		startPos += 8;
		qint32 cTexts = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 slideId = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 reserved3 = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		parserPersistDirectoryAtom(persistIdRef, TextType); }
		break;
	case RT_TextHeaderAtom:
		break;
	case RT_TextCharsAtom:
		break;
	case RT_TextBytesAtom:
		break;
	case RT_StyleTextPropAtom:
		break;
	case RT_SlideNumberMetaCharAtom:
		break;
	case RT_DateTimeMetaCharAtom:
		break;
	case RT_GenericDateMetaCharAtom:
		break;
	case RT_HeaderMetaCharAtom:
		break;
	case RT_FooterMetaCharAtom:
		break;
	case RT_RtfDateTimeMetaCharAtom:
		break;
	case RT_TextBookmarkAtom:
		break;
	case RT_TextSpecialInfoAtom:
		break;
	case RT_InteractiveInfo:
		break;
	case RT_TextInteractiveInfoAtom:
		break;
	default:return srcPos;
		break;
	}

	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserNotesList(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//NotesListWithTextContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_SlideListWithText)
	{
		return srcPos;
	}

	if (ST_RI(stVar) != 0x002)
	{
		return srcPos;
	}
	pos = ST_SP(stVar);
	do
	{
		pos = parserDocInfoListContainer(pos);
	} while (pos < ST_EP(stVar));
	
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserSlideShowDocInfoAtom(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//slideShowDocInfoAtom
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_SlideShowDocInfoAtom)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserNamedShows(quint32 pos)
{
	ST_Variable stVar;
	quint32 srcPos = pos;
	bool isValid = false;
	//NamedShowsContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_NamedShows)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserSummary(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//SummaryContainer
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_Summary)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserDocRoutingSlipAtom(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//DocRoutingSlipAtom
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_DocRoutingSlipAtom)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserPrintOptionsAtom(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	//PrintOptionsAtom
	isValid = physicalStruct(pos, stVar);
	if (!isValid || ST_TP(stVar) != RT_PrintOptionsAtom)
	{
		return srcPos;
	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserDocInfoListContainer(quint32 pos)
{
	ST_Variable stVar;

	quint32 srcPos = pos;
	bool isValid;
	
	//DocInfoListContainer
	isValid = physicalStruct(pos, stVar);
	pos = ST_SP(stVar);
	if (!isValid)
	{
		return srcPos;
	}
	if (ST_TP(stVar) == RT_NormalViewSetInfo9)
	{
		//TODO:和位置及状态有关，暂时不动
		//isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	}
	else if(ST_TP(stVar) == RT_ProgTags)
	{
		//TODO:扩展？暂时不动
		/*isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		quint16 recVer = ftHead & 0xF;
		quint16 recInstance = ftHead >> 8;*/

	}
	else if (ST_TP(stVar) == RT_NotesTextViewInfo9)
	{
		//TODO:缩放相关暂时不动
		//isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);

	}
	else if (ST_TP(stVar) == RT_OutlineViewInfo)
	{
		//TODO:大纲缩放相关暂时不动
	}
	else if (ST_TP(stVar) == RT_SlideViewInfo)
	{
		//幻灯片的页视图属性不动
	}
	else if (ST_TP(stVar) == RT_SorterViewInfo)
	{
		//幻灯片的顺序属性不动
	}
	else if (ST_TP(stVar) == RT_VbaInfo)
	{
		//VBA代码宏，不动
	}
	else
	{

	}
	return ST_EP(stVar);
}

quint32 ZTWPPDocument::parserPerSlideHeadersFootersContainer(quint32 pos)
{
	return quint32();
}

void ZTWPPDocument::parserSlide(quint32 pos)
{
	quint32 ftContainterSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
	quint32 containerEndPos = ftContainterSize + pos + 4;
	pos += 4;
	//SlideAtom
	quint32 srcPos = pos;
	bool isValid;

	ST_Variable slideVar;

	isValid = physicalStruct(pos, slideVar);
	if (!isValid)
	{
		return;
	}
	pos = ST_SP(slideVar);
	if (ST_TP(slideVar) == RT_SlideAtom)
	{
		//SlideLayoutType,用不到，暂时放着
		quint32 geom = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;
		//rgPlaceholderTypes,用不到，暂时放着
		quint8 rgPlaceholderType1 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType2 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType3 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType4 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType5 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType6 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType7 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		quint8 rgPlaceholderType8 = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 1;
		//如果是slideContainer不能是0，如果是master母版则必须是0
		quint32 masterIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;
		//备注页ID引用
		quint32 notesIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;
		quint16 slideFlags = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 2;

		quint8 fMasterObjects = slideFlags >> 15;
		quint8 fMasterScheme = (slideFlags >> 14) & 0x1;
		quint8 fMasterBackground = (slideFlags >> 13) & 0x1;
		quint16 reserved = slideFlags & 0x1FFF;
		
		quint16 unused = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 2;
	}

	do
	{
		ST_Variable stVar;

		bool isValid2 = physicalStruct(pos, stVar);
		pos = ST_SP(stVar);
		if (ST_TP(stVar) == RT_SlideShowSlideInfoAtom)
		{
			//自动切换幻灯片的时间单位毫秒
			qint32 slideTime = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 4;
			quint32 soundIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 4;
			quint8 effectDirection = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 1;
			quint8 effectType = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 1;
			quint16 zonghe = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			quint8 fManualAdvance = zonghe >> 15;
			quint8 reserved1 = (zonghe >> 14) & 0x1;
			quint8 fHidden = (zonghe >> 13) & 0x1;
			quint8 reserved2 = (zonghe >> 12) & 0x1;
			quint8 fSound = (zonghe >> 11) & 0x1;
			quint8 reserved3 = (zonghe >> 10) & 0x1;
			quint8 fLoopSound = (zonghe >> 9) & 0x1;
			quint8 reserved4 = (zonghe >> 8) & 0x1;
			quint8 fStopSound = (zonghe >> 7) & 0x1;
			quint8 reserved5 = (zonghe >> 6) & 0x1;
			quint8 fAutoAdvance = (zonghe >> 5) & 0x1;
			quint8 reserved6 = (zonghe >> 4) & 0x1;
			quint8 fCursorVisible = (zonghe >> 3) & 0x1;
			quint8 reserved7 = zonghe & 0x7;
			pos += 2;
			quint8 speed = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 1;
			//unused:为了字节对其需要跳过3字节
			pos += 3;
		}
		else if (ST_TP(stVar) == RT_HeadersFooters)//PerSlideHeadersFootersContainer
		{
			//HeadersFootersAtom
			pos += 8;
			qint16 formatId = qFromLittleEndian<qint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 2;
			quint16 zonghe = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			quint8 fHasDate = zonghe >> 15;
			quint8 fHasTodayDate = (zonghe >> 14) & 0x1;
			quint8 fHasUserDate = (zonghe >> 13) & 0x1;
			quint8 fHasSlideNumber = (zonghe >> 12) & 0x1;
			quint8 fHasHeader = (zonghe >> 11) & 0x1;
			quint8 fHasFooter = (zonghe >> 10) & 0x1;
			quint16 reserved = zonghe & 0x3FF;
			pos += 2;
			//userDateAtom
			ST_Variable uhVar;

			if (physicalStruct(pos, uhVar))
			{
				if (ST_TP(uhVar) == RT_CString)
				{
					pos = ST_SP(uhVar);
					if (ST_RI(uhVar) == 0x0)//userDateAtom
					{
						// 提取字符串数据
						const char* stringData = m_srcData.constData() + pos;
						QString qsContent = GetQString(stringData, ST_SZ(uhVar));
					}
					else if (ST_RI(uhVar) == 0x002)//FooterAtom
					{
						const char* stringData = m_srcData.constData() + pos;
						QString qsContent = GetQString(stringData, ST_SZ(uhVar));
					}
				}

				pos = ST_EP(uhVar);
			}
		}
		else if (ST_TP(stVar) == RT_RoundTripSlideSyncInfo12)//rtSlideSyncInfo12
		{
			//多用户同步用不着，暂时不管
			//pos += ftSize2;
		}
		else if (ST_TP(stVar) == RT_Drawing)
		{
			ST_Variable dwContainVar;

			if (physicalStruct(pos, dwContainVar))
			{
				if (ST_TP(dwContainVar) == 0xF002)
				{
					pos = ST_SP(dwContainVar);
					parserOfficeArtDgContainer(pos, ST_EP(dwContainVar));
				}
			}
		}
		else if (ST_TP(stVar) == RT_ColorSchemeAtom)
		{

		}
		else if (ST_TP(stVar) == RT_CString)//SlideNameAtom
		{

		}
		else if (ST_TP(stVar) == RT_ProgTags)//slideProgTagsContainer
		{

		}
		else if (ST_TP(stVar) == RT_RoundTripTheme12Atom
			|| ST_TP(stVar) == RT_RoundTripColorMapping12Atom
			|| ST_TP(stVar) == RT_RoundTripCompositeMasterId12Atom
			|| ST_TP(stVar) == RT_RoundTripSlideSyncInfo12
			|| ST_TP(stVar) == RT_RoundTripAnimationHashAtom12Atom
			|| ST_TP(stVar) == RT_RoundTripAnimationAtom12Atom
			|| ST_TP(stVar) == RT_RoundTripContentMasterId12Atom)//RoundTripSlideRecord
		{

		}
		else
		{

		}
		pos = ST_EP(stVar);
	} while (pos < containerEndPos);

}

void ZTWPPDocument::parserOfficeArtDgContainer(quint32 pos, quint32 endPos)
{
	ST_Variable tmpVar;
	bool alreadyParserGShape = false;
	bool alreadyParserShape = false;
	do
	{
		if (!physicalStruct(pos, tmpVar))
		{
			break;
		}
		pos = ST_SP(tmpVar);
		switch (ST_TP(tmpVar))
		{
		case 0xF008://drawingData:OfficeArtFDG 
		{
			if (ST_RI(tmpVar) <= 0xFFE && ST_TP(tmpVar) == 0xF008)
			{
				
				quint32 csp = GetFlagData<quint32>(m_srcData, pos);//shape count
				quint32 spidCur = GetFlagData<quint32>(m_srcData, pos);//MSOSPID 		
			}
		}
			break;
		case 0xF118://regroupItems:OfficeArtFRITContainer 
		{
			//rgfrit 
			quint16 count = ST_RI(tmpVar);
			for (quint16 i = 0; i < count; ++i)
			{
				quint16 fridNew = GetFlagData<quint16>(m_srcData, pos);
				quint16 fridOld = GetFlagData<quint16>(m_srcData, pos);
				if (pos < ST_SZ(tmpVar))
				{
					break;
				}
			}
		}
			break;
		case 0xF003://groupShape:OfficeArtSpgrContainer 
		{
			//OfficeArtSpgrContainerFileBlock
			//alreadyParserGShape
			do
			{
				ST_Variable tmpVar2;
				if (!physicalStruct(pos, tmpVar2))
				{
					return;
				}
				if (ST_TP(tmpVar2) == 0xF004)
				{
					parserOfficeArtSpContainer(ST_SP(tmpVar2), ST_EP(tmpVar2));
				}
				pos = ST_EP(tmpVar2);
			} while (pos < ST_EP(tmpVar));
			
			/*else if(ST_TP(tmpVar2) == 0xF003)
			{

			}
			else
			{

			}*/
		}
			break;
		case 0xF004://shape:OfficeArtSpContainer
		{
			parserOfficeArtSpContainer(pos , ST_EP(tmpVar));
		}
		break;
		case 0xF005://solvers1:OfficeArtSolverContainer 
		{

		}
		break;
		default:
			break;
		}
		pos = ST_EP(tmpVar);
	} while (pos < endPos);
}

void ZTWPPDocument::parserOfficeArtFRITContainer(quint32 pos)
{
}

void ZTWPPDocument::parserOfficeArtSpContainer(quint32 pos, quint32 endPos)
{
	ST_Variable stVar;
	do
	{
		if (!physicalStruct(pos, stVar))
		{
			return;
		}
		pos = ST_SP(stVar);
		switch (ST_TP(stVar))
		{
		case 0xF009://shapeGroup:OfficeArtFSPGR
		{
			qint32 xLeft = GetFlagData<qint32>(m_srcData, pos);
			qint32 yTop = GetFlagData<qint32>(m_srcData, pos);
			qint32 xRight = GetFlagData<qint32>(m_srcData, pos);
			qint32 yBottom = GetFlagData<qint32>(m_srcData, pos);
		}
		break;
		case 0xF00A://shapeProp:OfficeArtFSP
		{
			qint16 MSOSPT = ST_RI(stVar);
			qint32 spid = GetFlagData<qint32>(m_srcData, pos);//MSOSPDI
			quint32 flag = GetFlagData<quint32>(m_srcData, pos);
			quint8 fGroup = flag & 0x1;
			quint8 fChild = (flag >> 1) & 0x1;
			quint8 fPatriarch = (flag >> 2) & 0x1;
			quint8 fDeleted = (flag >> 3) & 0x1;
			quint8 fOleShape = (flag >> 4) & 0x1;
			quint8 fHaveMaster = (flag >> 5) & 0x1;
			quint8 fFlipH = (flag >> 6) & 0x1;
			quint8 fFlipV = (flag >> 7) & 0x1;
			quint8 fConnector = (flag >> 8) & 0x1;
			quint8 fHaveAnchor = (flag >> 9) & 0x1;
			quint8 fBackground = (flag >> 10) & 0x1;
			quint8 fHaveSpt = (flag >> 11) & 0x1;
		}
		break;
		case 0xF11D://deletedShape:OfficeArtFPSPL
		{
			quint32 flag = GetFlagData<quint32>(m_srcData, pos);
			quint32 spid = flag >> 2;
			quint8 reserved1 = (flag >> 1) & 0x01;
			quint8 fLast = flag & 0x01;
		}
		break;
		case 0xF00B://shapePrimaryOptions:OfficeArtFOPT
		{
			quint32 count = ST_RI(stVar);//OfficeArtRGFOPTE的数量
			
			for (int foptIndex = 0; foptIndex < count; ++foptIndex)
			{
				//OfficeArtFOPTE
				quint16 opidHead = GetFlagData<quint16>(m_srcData, pos);
				quint16 opid = opidHead & 0x3FFF;
				quint8 fBid = (opidHead >> 14) & 0x1;
				quint8 fComplex = (opidHead >> 15) & 0x1;
				qint32 op = GetFlagData<qint32>(m_srcData, pos);
				if (fComplex == 0x1)//数据的大小
				{
					
				}
				else //数据本身
				{
					//GetQString()
				}
				
			}
			qint32 sizexs = 0xa;
			QByteArray da = m_srcData.mid(pos, sizexs);
			QString qdd = GetQString(m_srcData, sizexs);
			qDebug() << qdd;
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < endPos);


}
