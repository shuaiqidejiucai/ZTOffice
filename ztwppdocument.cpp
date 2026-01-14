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
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	quint32 pos = 0;
	bool isValid;

	do
	{
		isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid)
		{
			m_typeOffsetList.append(QPair<quint16, quint32>(ftType, pos));
		}
		pos = endPos;
	} while (isValid);

	parserDocument();
}

bool ZTWPPDocument::physicalStruct(quint32 pos, quint16& ftHead, quint16& ftType, quint32& ftSize, quint32& startPos, quint32& endPos)
{
	if (pos + 8 < m_srcData.size())
	{
		ftHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 2;
		ftType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 2;
		ftSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;
		if (pos + ftSize < m_srcData.size())
		{
			startPos = pos;
			endPos = pos + ftSize;
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
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	bool isValid;

	bool isFind = false;
	QList<QPair<quint16, quint32> > documentList = findType(RT_Document);
	/*std::function<quint32(quint32)> func = std::bind(&ZTWPPDocument::parserExObjList, this, std::placeholders::_1);*/
	for (const QPair<quint16, quint32>& tmpPair : documentList)
	{
		isFind = true;
		isValid = physicalStruct(tmpPair.second, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid)
		{
			quint32 tmpPos = parserDocumentAtom(startPos);
			quint16 ftHead2 = 0;
			quint16 ftType2 = 0;
			quint32 ftSize2 = 0;
			quint32 startPos2 = 0;
			quint32 endPos2 = 0;
			bool isValid2 = false;
			do
			{
				isValid2 = physicalStruct(tmpPos, ftHead2, ftType2, ftSize2, startPos2, endPos2);
				quint16 recVer = ftHead2 & 0xF;
				quint16 recInstance = ftHead2 >> 8;
				if (!isValid2)
				{
					break;
				}
				if (ftType2 == RT_ExternalObjectList)
				{
					tmpPos = parserExObjList(tmpPos);
				}
				else if (ftType2 == RT_Environment)
				{
					tmpPos = parserDocumentTextInfoContainer(tmpPos);
				}
				else if(ftType2 == RT_SoundCollection)
				{
					tmpPos = parserSoundCollection(tmpPos);
				}
				else if (ftType2 == RT_DrawingGroup)
				{
					tmpPos = parserDrawingGroup(tmpPos);
				}
				else if (ftType2 == RT_SlideListWithText)
				{
					if (recInstance == 0x001)
					{
						tmpPos = parserMasterList(tmpPos);
					}
					else if (recInstance == 0x000)
					{
						tmpPos = parserSlideList(tmpPos);
					}
					else if(recInstance == 0x002)
					{
						tmpPos = parserNotesList(tmpPos);
					}
					else
					{
						tmpPos = endPos2;
					}
				}
				else if (ftType2 == RT_List)
				{
					tmpPos = parserDocInfoList(tmpPos);
				}
				else if(ftType2 == RT_HeadersFooters)
				{
					if (recInstance == 0x000)
					{
						tmpPos = endPos2;
						//tmpPos = parserPerSlideHeadersFootersContainer(tmpPos);
					}
					else if (recInstance == 0x003)
					{
						tmpPos = parserSlideHF(tmpPos);
					}
					else if(recInstance == 0x004)
					{
						tmpPos = parserNotesHF(tmpPos);
					}
					else
					{
						tmpPos = endPos2;
					}
				}
				else if (ftType2 == RT_SlideShowDocInfoAtom)
				{
					tmpPos = parserSlideShowDocInfoAtom(tmpPos);
				}
				else if(ftType2 == RT_NamedShows)
				{
					tmpPos = parserNamedShows(tmpPos);
				}
				else if(ftType2 == RT_Summary)
				{
					tmpPos = parserSummary(tmpPos);
				}
				else if(ftType2 == RT_DocRoutingSlipAtom)
				{
					tmpPos = parserDocRoutingSlipAtom(tmpPos);
				}
				else if(ftType2 == RT_PrintOptionsAtom)
				{
					tmpPos = parserPrintOptionsAtom(tmpPos);
				}
				else
				{
					tmpPos = endPos2;
				}
			} while (tmpPos < endPos);
		}
	}

	return endPos;
}

quint32 ZTWPPDocument::parserDocumentAtom(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;

	bool isFind = false;
	do
	{
		isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid && ftType == RT_DocumentAtom)
		{
			isFind = true;
			break;
		}
	} while (false);

	if (isFind)
	{
		quint16 recVer = ftHead & 0xF;
		quint16 recInstance = ftHead >> 8;
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
		return endPos;
	}
	return srcPos;
}

quint32 ZTWPPDocument::parserExObjList(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	bool isValid;

	bool isFind = false;
	do
	{
		isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid && ftType == RT_ExternalObjectList)
		{
			isFind = true;
			break;
		}
	} while (false);

	if (isFind)
	{
		quint16 recVer = ftHead & 0xF;
		quint16 recInstance = ftHead >> 8;
		quint32 exObj = 0;
		quint32 tmpPos = parserExObjListAtom(startPos);
		if (ftSize - 12 > 0)//有容器
		{
			parserExObjListSubContainer(tmpPos);
		}
		return endPos;
	}
	return pos;
}

quint32 ZTWPPDocument::parserExObjListAtom(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;

	bool isFind = false;
	do
	{
		isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid && ftType == RT_ExternalObjectListAtom)
		{
			isFind = true;
			break;
		}
	} while (false);

	if (isFind)
	{
		quint16 recVer = ftHead & 0xF;
		quint16 recInstance = ftHead >> 8;
		qint32 exObjIdSeed = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;
		return endPos;
	}
	return srcPos;
}

void ZTWPPDocument::parserExObjListSubContainer(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;


	bool isValid;

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
		isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid && subContainerList.contains((HeaderType)ftType))
		{
			isFind = true;
			quint16 recVer = ftHead & 0xF;
			quint16 recInstance = ftHead >> 8;
			if (ftType == RT_ExternalAviMovie)
			{

			}
			else if (ftType == RT_ExternalCdAudio)
			{

			}
			else if (ftType == RT_ExternalOleControl)
			{

			}
			else if (ftType == RT_ExternalHyperlink)
			{

			}
			else if (ftType == RT_ExternalMciMovie)
			{

			}
			else if (ftType == RT_ExternalMidiAudio)
			{

			}
			else if (ftType == RT_ExternalOleEmbed)
			{
				parserExOleEmbedContainer(startPos);
			}
			else if (ftType == RT_ExternalOleLink)
			{

			}
			else if (ftType == RT_ExternalWavAudioEmbedded)
			{

			}
			else if (ftType == RT_ExternalWavAudioLink)
			{

			}
			else
			{

			}
			pos += ftSize;
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
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	bool isValid;

	if (true)
	{
		//ExOleEmbedAtom
		isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		if (!isValid || ftType != RT_ExternalOleEmbedAtom)
		{
			return;
		}
		quint16 exOleEmbedAtomRecVer = ftHead & 0xF;
		quint16 exOleEmbedAtomRecInstance = ftHead >> 8;

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
		isValid = physicalStruct(startPos, ftHead, ftType, ftSize, startPos, endPos);
		if (!isValid || ftType != RT_ExternalOleObjectAtom)
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
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	bool isValid;
	//DocumentTextInfoContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_Environment)
	{
		return pos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserSoundCollection(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	bool isValid;
	//ExOleEmbedAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_SoundCollection)
	{
		return pos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserDrawingGroup(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//ExOleEmbedAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_DrawingGroup)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserMasterList(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//MasterListWithTextContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_SlideListWithText)
	{
		return srcPos;
	}
	quint16 recVer = ftHead & 0xF;
	quint16 recInstance = ftHead >> 8;
	if (recInstance != 0x001)
	{
		return srcPos;
	}

	//MasterPersistAtom
	for (int i = 0; i < ftSize; ++i)
	{

	}
	

	return endPos;
}

quint32 ZTWPPDocument::parserDocInfoList(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//DocInfoListContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_List)
	{
		return srcPos;
	}

	do
	{
		pos = parserDocInfoListContainer(pos);
	} while (pos < endPos);

	return endPos;
}

quint32 ZTWPPDocument::parserSlideHF(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//SlideHeadersFootersContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_HeadersFooters)
	{
		return srcPos;
	}
	quint16 recVer = ftHead & 0xF;
	quint16 recInstance = ftHead >> 8;
	if (recInstance != 0x003)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserNotesHF(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//NotesHeadersFootersContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_HeadersFooters)
	{
		return srcPos;
	}
	quint16 recVer = ftHead & 0xF;
	quint16 recInstance = ftHead >> 8;
	if (recInstance != 0x004)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserSlideList(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//SlideListWithTextContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_SlideListWithText)
	{
		return srcPos;
	}
	quint16 recVer = ftHead & 0xF;
	quint16 recInstance = ftHead >> 8;
	if (recInstance != 0x000)
	{
		return srcPos;
	}
	pos = startPos;
	do
	{
		pos = parserSlideListWithTextSubContainerOrAtom(pos);
	} while (pos < endPos);

	return endPos;
}

quint32 ZTWPPDocument::parserSlideListWithTextSubContainerOrAtom(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//SlideListWithTextSubContainerOrAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	
	if (!isValid)
	{
		return srcPos;
	}
	
	quint16 recVer = ftHead & 0xF;
	quint16 recInstance = ftHead >> 8;
	/*if (recInstance != 0x000)
	{
		return srcPos;
	}*/

	if (ftType == RT_SlidePersistAtom)
	{
		quint32 persistIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		//TODO:这里有8字节的内容现在用不到不解析
		startPos += 8;
		qint32 cTexts = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 slideId = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		quint32 reserved3 = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + startPos));
		startPos += 4;
		parserPersistDirectoryAtom(persistIdRef, TextType);

	}
	else if(ftType == RT_TextHeaderAtom)
	{

	}
	else if (ftType == RT_TextCharsAtom)
	{

	}
	else if (ftType == RT_TextBytesAtom)
	{

	}
	else if (ftType == RT_StyleTextPropAtom)
	{

	}
	else if (ftType == RT_SlideNumberMetaCharAtom)
	{

	}
	else if (ftType == RT_DateTimeMetaCharAtom)
	{

	}
	else if (ftType == RT_GenericDateMetaCharAtom)
	{

	}
	else if (ftType == RT_HeaderMetaCharAtom)
	{

	}
	else if (ftType == RT_FooterMetaCharAtom)
	{

	}
	else if (ftType == RT_RtfDateTimeMetaCharAtom)
	{

	}
	else if (ftType == RT_TextBookmarkAtom)
	{

	}
	else if (ftType == RT_TextSpecialInfoAtom)
	{

	}
	else if (ftType == RT_InteractiveInfo)
	{

	}
	else if (ftType == RT_TextInteractiveInfoAtom)
	{

	}
	else
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserNotesList(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//NotesListWithTextContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_SlideListWithText)
	{
		return srcPos;
	}
	quint16 recVer = ftHead & 0xF;
	quint16 recInstance = ftHead >> 8;
	if (recInstance != 0x002)
	{
		return srcPos;
	}
	pos = startPos;
	do
	{
		pos = parserDocInfoListContainer(pos);
	} while (pos < endPos);
	
	return endPos;
}

quint32 ZTWPPDocument::parserSlideShowDocInfoAtom(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//slideShowDocInfoAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_SlideShowDocInfoAtom)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserNamedShows(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//NamedShowsContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_NamedShows)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserSummary(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//SummaryContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_Summary)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserDocRoutingSlipAtom(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//DocRoutingSlipAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_DocRoutingSlipAtom)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserPrintOptionsAtom(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	//PrintOptionsAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_PrintOptionsAtom)
	{
		return srcPos;
	}
	return endPos;
}

quint32 ZTWPPDocument::parserDocInfoListContainer(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;
	
	//DocInfoListContainer
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	pos = startPos;
	if (!isValid)
	{
		return srcPos;
	}
	if (ftType == RT_NormalViewSetInfo9)
	{
		//TODO:和位置及状态有关，暂时不动
		//isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	}
	else if(ftType == RT_ProgTags)
	{
		//TODO:扩展？暂时不动
		/*isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
		quint16 recVer = ftHead & 0xF;
		quint16 recInstance = ftHead >> 8;*/

	}
	else if (ftType == RT_NotesTextViewInfo9)
	{
		//TODO:缩放相关暂时不动
		//isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);

	}
	else if (ftType == RT_OutlineViewInfo)
	{
		//TODO:大纲缩放相关暂时不动
	}
	else if (ftType == RT_SlideViewInfo)
	{
		//幻灯片的页视图属性不动
	}
	else if (ftType == RT_SorterViewInfo)
	{
		//幻灯片的顺序属性不动
	}
	else if (ftType == RT_VbaInfo)
	{
		//VBA代码宏，不动
	}
	else
	{

	}
	return endPos;
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
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;
	quint32 srcPos = pos;
	bool isValid;

	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	pos = startPos;
	if (!isValid)
	{
		return;
	}
	pos = startPos;
	if (ftType == RT_SlideAtom)
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
		quint16 ftHead2 = 0;
		quint16 ftType2 = 0;
		quint32 ftSize2 = 0;
		quint32 startPos2 = 0;
		quint32 endPos2 = 0;
		bool isValid2 = physicalStruct(pos, ftHead2, ftType2, ftSize2, startPos2, endPos2);
		pos = startPos2;
		if (ftType2 == RT_SlideShowSlideInfoAtom)
		{
			//自动切换幻灯片的时间单位毫秒
			qint32 slideTime = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 4;
			quint32 soundIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 4;
			quint8 effectDirection = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
			pos += 1;
			quint8 effectDirection = qFromLittleEndian<quint8>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
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
		else if (ftType2 == RT_HeadersFooters)//PerSlideHeadersFootersContainer
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
			quint16 uhHead = 0;
			quint16 uhType = 0;
			quint32 uhSize = 0;
			quint32 uhStartPos = 0;
			quint32 uhEndPos = 0;
			if (physicalStruct(pos, uhHead, uhType, uhSize, uhStartPos, uhEndPos))
			{
				if (uhType == RT_CString)
				{
					quint16 recVer = ftHead & 0xF;
					quint16 recInstance = ftHead >> 8;
					pos = uhStartPos;
					if (recInstance == 0x0)//userDateAtom
					{
						// 提取字符串数据
						const char* stringData = m_srcData.constData() + pos;
						QString qsContent = GetQString(stringData, uhSize);
					}
					else if (recInstance == 0x002)//FooterAtom
					{
						const char* stringData = m_srcData.constData() + pos;
						QString qsContent = GetQString(stringData, uhSize);
					}
				}

				pos = uhEndPos;
			}
		}
		else if (ftType2 == RT_RoundTripSlideSyncInfo12)//rtSlideSyncInfo12
		{
			//多用户同步用不着，暂时不管
			//pos += ftSize2;
		}
		else if (ftType2 == RT_Drawing)
		{
			quint16 dwHead = 0;
			quint16 dwType = 0;
			quint32 dwSize = 0;
			quint32 dwStartPos = 0;
			quint32 dwEndPos = 0;
			if (physicalStruct(pos, dwHead, dwType, dwSize, dwStartPos, dwEndPos))
			{
				pos = dwStartPos;
				quint16 ordcHead = 0;
				quint16 ordcType = 0;
				quint32 ordcSize = 0;
				quint32 ordcStartPos = 0;
				quint32 ordcEndPos = 0;
				//OfficeArtDgContainer
				if (physicalStruct(pos, ordcHead, ordcType, ordcSize, ordcStartPos, ordcEndPos))
				{
					if (ordcType == 0xF002)
					{
						pos = ordcStartPos;

					}
				}
			}
		}
		else if (ftType2 == RT_ColorSchemeAtom)
		{

		}
		else if (ftType2 == RT_CString)//SlideNameAtom
		{

		}
		else if (ftType2 == RT_ProgTags)//slideProgTagsContainer
		{

		}
		else if (ftType2 == RT_RoundTripTheme12Atom
			|| ftType2 == RT_RoundTripColorMapping12Atom
			|| ftType2 == RT_RoundTripCompositeMasterId12Atom
			|| ftType2 == RT_RoundTripSlideSyncInfo12
			|| ftType2 == RT_RoundTripAnimationHashAtom12Atom
			|| ftType2 == RT_RoundTripAnimationAtom12Atom
			|| ftType2 == RT_RoundTripContentMasterId12Atom)//RoundTripSlideRecord
		{

		}
		else
		{

		}
		pos = endPos2;
	} while (pos < containerEndPos);

}
