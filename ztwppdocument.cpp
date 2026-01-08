#include "ztwppdocument.h"
#include <qdir.h>
#include <qmath.h>
#include <qtemporaryfile.h>
#include <qdebug.h>
using namespace ZT_Libolecf;
ZTWPPDocument::ZTWPPDocument() {}

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
	for (const QPair<quint16, quint32>& tmpPair : documentList)
	{
		isFind = true;
		isValid = physicalStruct(tmpPair.second, ftHead, ftType, ftSize, startPos, endPos);
		if (isValid)
		{
			quint32 tmpPos = parserDocumentAtom(startPos);
			tmpPos = parserExObjList(tmpPos);
			tmpPos = parserDocumentTextInfoContainer(tmpPos);
			tmpPos = paserSoundCollection(tmpPos);
			tmpPos = paserDrawingGroup(tmpPos);
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
		quint32 tmpPos = parserExObjListAtom(startPos, exObj);
		if (ftSize - 12 > 0)//有容器
		{
			parserExObjListSubContainer(tmpPos, endPos);
		}
		return endPos;
	}
	return pos;
}

quint32 ZTWPPDocument::parserExObjListAtom(quint32 pos, quint32& count)
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
		count = ftSize;
		quint16 recVer = ftHead & 0xF;
		quint16 recInstance = ftHead >> 8;
		qint32 exObjIdSeed = qFromLittleEndian<qint32>(reinterpret_cast<const uchar*>(m_srcData.constData() + pos));
		pos += 4;
		return endPos;
	}
	return srcPos;
}

void ZTWPPDocument::parserExObjListSubContainer(quint32 pos, quint32 exObjCount)
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
	} while (clac < exObjCount);

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

bool ZTWPPDocument::parserPersistDirectoryAtom(quint32 idRef)
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
				extratorAttachment(rgPersistOffset);
				break;
			}
			pos += 4;
		}
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

quint32 ZTWPPDocument::parserDocumentTextInfoContainer(quint32 pos)
{
	quint16 ftHead = 0;
	quint16 ftType = 0;
	quint32 ftSize = 0;
	quint32 startPos = 0;
	quint32 endPos = 0;

	bool isValid;
	//ExOleEmbedAtom
	isValid = physicalStruct(pos, ftHead, ftType, ftSize, startPos, endPos);
	if (!isValid || ftType != RT_Environment)
	{
		return pos;
	}
	return endPos;
}

quint32 ZTWPPDocument::paserSoundCollection(quint32 pos)
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

quint32 ZTWPPDocument::paserDrawingGroup(quint32 pos)
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


