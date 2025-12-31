#include "mainwindow.h"

#include <QApplication>
#include "libolecf.h"
#include <qendian.h>
#include <QFile>
#include <QPair>
#include <qdebug.h>
#include <QStringList>
#include "zlib.h"
enum EU_XLSReordType
{
    MsoDrawingReordType = 236,
    ObjReordType        = 93
};

enum EU_ContinueType
{
    REC_MSODRAWING_CONT = 0x00EC,
    REC_MSODRAWING_CONT2 = 0x003C /*或 0x003C 视版本*/ 
};

const quint16 Container_Header = 0xF;
const quint16 OfficeArtDgContainer_Type = 0xF002;
const quint16 OfficeArtFDG_Type = 0xF008;
const quint16 OfficeArtClientData = 0xF011;

const QString DOCXCLSID = "{F4754C9B-64F5-4B40-8AF4-679732AC0607}";
const QString XlSXCLSID = "{F4754C9B-64F5-4B40-8AF4-679732AC0607}";//占位
const QString PPTXCLSID = "{F4754C9B-64F5-4B40-8AF4-679732AC0607}";//占位

struct ST_BasicData
{
    quint16 dataType;
    quint16 dataSize;
    QByteArray data;
};
typedef QPair<quint16, quint32> LogicHeadPair;
typedef QPair<quint16, quint16> BIFFHeadPair;

bool isDocument(QStringList oleStruct)
{
    return false;
}

QString getOleItemName(libolecf_item_t* pItem)
{
    size_t stringSize = 0;
    libolecf_item_get_utf8_name_size(pItem, &stringSize, nullptr);
    QByteArray nameData;
    nameData.resize(stringSize);
    libolecf_item_get_utf8_name(pItem, (uint8_t*)nameData.data(), stringSize, nullptr);
    QString nodeName = QString::fromUtf8(nameData);
    return nodeName;
}

QString getCompObjCLSID(libolecf_item_t* pComObjItem)
{
    QString qsClsid;
    if (pComObjItem)
    {
        QByteArray data;
        uint32_t stream_size = 0;
        libolecf_item_get_size(pComObjItem, &stream_size, nullptr);

        //限制图片大小不超过100M防止内存过大
        if (stream_size > 0)
        {
            data.resize(stream_size);
            libolecf_stream_read_buffer(pComObjItem, (uint8_t*)data.data(), stream_size, nullptr);
            if (!data.isEmpty())
            {
                qsClsid = data.mid(12, 15);
            }
        }
    }
    return qsClsid;
}
#include "qunzip/include/quazip.h"
#include <qbuffer.h>
#include <qtextcodec.h>



static bool parseOle10Native2(const QByteArray& src, ST_VarantFile& stOleFile)
{
	if (src.size() < 12) return false;
	auto readZ = [&](int& pos)->QByteArray {
        if (pos >= src.size()) return {};

        int start = pos;
        // 直接找到 '\0'，不要跳过开头的 '\0'
        while (pos < src.size() && src[pos] != '\0') {
            ++pos;
        }

        QByteArray s = src.mid(start, pos - start);

        if (pos < src.size() && src[pos] == '\0') {
            ++pos;  // 跳过终止符
        }

        return s;
	};

	int offset = 0;
	quint32 totalSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(src.constData() + offset));
	offset += 4;
    //offset += 2;
	bool ok = false;
	if (offset + 2 >= src.size())
	{
		return false;
	}
	quint16 filePrexLength = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(src.constData() + offset));
	offset += 2;
	QTextCodec* code = QTextCodec::codecForName("GBK");

	QByteArray label = readZ(offset);
	if (!label.isEmpty())
	{
		qDebug() << label;
	}

	QByteArray fileNameData = readZ(offset);
	if (!fileNameData.isEmpty())
	{
		stOleFile.qsFileName = code->toUnicode(fileNameData);
	}

	QByteArray filePathData = readZ(offset);
	if (!filePathData.isEmpty())
	{
		stOleFile.qsFilePath = code->toUnicode(filePathData);
	}
	if (offset + 4 >= src.size())
	{
		return false;
	}
	quint32 mark = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(src.constData() + offset));
	offset += 4;
	if (offset + 4 > src.size())
	{
		return false;
	}
	quint32 tempPathLen = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(src.constData() + offset));
	offset += 4;
	QByteArray tempPathBa = readZ(offset);
	if (!tempPathBa.isEmpty())
	{
		stOleFile.qsTmpFilePath = code->toUnicode(tempPathBa);
	}
	if (offset + 4 > src.size())
	{
		return false;
	}
	quint32 datasize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(src.constData() + offset));
	offset += 4;
	if (offset + datasize > src.size())
	{
		return false;
	}
	QByteArray srcData = src.mid(offset, datasize);
	stOleFile.fileData = srcData;
	return true;
}


static bool parseOle10Native(const QByteArray& src, ST_VarantFile& stOleFile)
{
    if (src.size() < 12) return false;

    int offset = 0;

    // 1. totalSize
    quint32 totalSize = qFromLittleEndian<quint32>(
        reinterpret_cast<const uchar*>(src.constData() + offset)
        );
    offset += 4;

    // 2. signature/flags1
    quint16 signature = qFromLittleEndian<quint16>(
        reinterpret_cast<const uchar*>(src.constData() + offset)
        );
    offset += 2;

    QTextCodec* gbkCodec = QTextCodec::codecForName("GBK");

    if (signature == 0x0002) {
        // ===== Apache POI 的启发式判断 =====
        uchar firstByte = (offset < src.size()) ? static_cast<uchar>(src[offset]) : 0;

        if (firstByte > 0 && firstByte < 32) {
            // Compact 模式：label 的第一个字节是控制字符
            int dataSize = totalSize - 2;  // 减去 signature
            if (offset + dataSize <= src.size()) {
                stOleFile.fileData = src.mid(offset, dataSize);
                return true;
            }
        }
        else {
            // Parsed 模式：标准格式

            // ===== LibreOffice 的字符串跳过策略 =====
            auto skipNullTerm = [&]() -> QByteArray {
                int start = offset;
                while (offset < src.size() && src[offset] != '\0') ++offset;
                QByteArray result = src.mid(start, offset - start);
                if (offset < src.size()) ++offset;  // 跳过 '\0'
                return result;
            };

            // label
            QByteArray label = skipNullTerm();
            stOleFile.qsFileName = gbkCodec->toUnicode(label);

            // fileName
            QByteArray fileName = skipNullTerm();
            stOleFile.qsFilePath = gbkCodec->toUnicode(fileName);

            // 尝试读取可选的 flags2 + unknown1 (4 bytes)
            if (offset + 4 <= src.size()) {
                offset += 4;
            }

            // 尝试读取可选的 command（带长度前缀）
            if (offset + 4 <= src.size()) {
                quint32 commandLen = qFromLittleEndian<quint32>(
                    reinterpret_cast<const uchar*>(src.constData() + offset)
                    );
                if (commandLen > 0 && commandLen < 1024 &&
                    offset + 4 + commandLen <= src.size()) {
                    offset += 4 + commandLen;
                }
            }

            // dataSize
            if (offset + 4 <= src.size()) {
                quint32 dataSize = qFromLittleEndian<quint32>(
                    reinterpret_cast<const uchar*>(src.constData() + offset)
                    );
                offset += 4;

                if (offset + dataSize <= src.size()) {
                    stOleFile.fileData = src.mid(offset, dataSize);
                    return true;
                }
            }
        }
    }

    // ===== Unparsed 模式（兜底）=====
    // 从当前位置读取到 totalSize 指定的末尾
    int expectedEnd = 4 + totalSize;
    int remainingSize = expectedEnd - offset;
    if (remainingSize > 0 && offset + remainingSize <= src.size()) {
        stOleFile.fileData = src.mid(offset, remainingSize);
        return true;
    }

    return false;
}


EU_DocumentType getPackage(QByteArray zipBytes)//查看内部结构是不是docx等
{
    QBuffer buffer;
    buffer.setData(zipBytes);
    if (!buffer.open(QIODevice::ReadOnly))
    {
        qWarning() << "QBuffer open fail";
        return EU_DocumentType::EU_NoType;
    }

    QuaZip zip(&buffer);
    if (!zip.open(QuaZip::mdUnzip))
    {
        qWarning() << "QuaZip open fail, code =" << zip.getZipError();
        return EU_DocumentType::EU_NoType;
    }

    bool isDocx = true;
    isDocx = isDocx && zip.setCurrentFile("[Content_Types].xml");
    isDocx = isDocx && zip.setCurrentFile("_rels/.rels");
    isDocx = isDocx && zip.setCurrentFile("word/document.xml");
    
    bool isXlsx = true;
    isXlsx = isXlsx && zip.setCurrentFile("[Content_Types].xml");
    isXlsx = isXlsx && zip.setCurrentFile("_rels/.rels");
    isXlsx = isXlsx && zip.setCurrentFile("xl/workbook.xml");
    isXlsx = isXlsx && zip.setCurrentFile("xl/_rels/workbook.xml.rels");
    isXlsx = isXlsx && zip.setCurrentFile("xl/worksheets/");

    bool isPptx = true;
    isPptx = isPptx && zip.setCurrentFile("[Content_Types].xml");
    isPptx = isPptx && zip.setCurrentFile("_rels/.rels");
    isPptx = isPptx && zip.setCurrentFile("ppt/presentation.xml");
    isPptx = isPptx && zip.setCurrentFile("ppt/_rels/presentation.xml.rels");
    isPptx = isPptx && zip.setCurrentFile("ppt/slides/");

    if (isDocx)
    {
        return EU_DocumentType::EU_DOCXType;
    }
    else if(isXlsx)
    {
        return EU_DocumentType::EU_XLSXType;
    }
    else if(isPptx)
    {
        return EU_DocumentType::EU_PPTXType;
    }
    return EU_DocumentType::EU_NoType;
}

bool hasOleTreeItem(libolecf_item_t* intputItem, QString nodeName, libolecf_item_t** subItem, bool isRegex = false, bool isOutPut = false)
{
    if (isRegex)
    {
        int nItemCount = 0;
        libolecf_item_get_number_of_sub_items(intputItem, &nItemCount, nullptr);

        for (int i = 0; i < nItemCount; ++i)
        {
            libolecf_item_t* subTmpItem = nullptr;
            libolecf_item_get_sub_item(intputItem, i, &subTmpItem, nullptr);
            if (!subTmpItem)
            {
                continue;
            }
            size_t stringSize = 0;
            libolecf_item_get_utf8_name_size(subTmpItem, &stringSize, nullptr);
            QByteArray nameData;
            nameData.resize(stringSize);
            libolecf_item_get_utf8_name(subTmpItem, (uint8_t*)nameData.data(), stringSize, nullptr);
            QString nodeItemName = QString::fromUtf8(nameData);
            if (nodeItemName.contains(nodeName))
            {
                if (isOutPut)
                {
                    *subItem = subTmpItem;
                    return true;
                }
            }
            libolecf_item_free(&subTmpItem, nullptr);
            subTmpItem = nullptr;
        }
    }
    else
    {
        libolecf_item_t* subTmpItem = nullptr;
        libolecf_item_get_sub_item_by_utf8_path(intputItem, (uint8_t*)nodeName.toUtf8().data(), nodeName.toUtf8().size(), &subTmpItem, nullptr);
        if (subTmpItem)
        {
            if (isOutPut)
            {
                *subItem = subTmpItem;
            }
            else
            {
                libolecf_item_free(&subTmpItem, nullptr);
                subTmpItem = nullptr;
            }
            return true;
        }
    }
    
    return false;
}

QByteArray getOleItemData(libolecf_item_t* intputItem)
{
    QByteArray data;
    if (intputItem)
    {

        // 读取流数据
        uint32_t stream_size = 0;
        libolecf_item_get_size(intputItem, &stream_size, nullptr);
        if (stream_size > 0)
        {
            data.resize(stream_size);
            libolecf_stream_read_buffer(intputItem, (uint8_t*)data.data(), stream_size, nullptr);
        }
    }
    return data;
}

EU_DocumentType getOleFileFormat(libolecf_item_t*intputItem, bool &haveOutput, libolecf_item_t** outputItem)
{
    /*int subItemCount = 0;
    libolecf_item_get_number_of_sub_items(intputItem, &subItemCount, nullptr);*/

    bool isDoc = true;
    isDoc = isDoc && hasOleTreeItem(intputItem, "WordDocument", nullptr);
    
    bool isXls = true;
    isXls = isXls && hasOleTreeItem(intputItem, "Workbook", nullptr);

    bool isPpt = true;
    isPpt = isPpt && hasOleTreeItem(intputItem, "PowerPoint Document", nullptr);
    isPpt = isPpt && hasOleTreeItem(intputItem, "Current User", nullptr);
    EU_DocumentType documentType = EU_DocumentType::EU_NoType;
    if (isDoc)
    {
        if (hasOleTreeItem(intputItem, "WpsCustomData", nullptr))
        {
            documentType = EU_WPSType;
        }
        else
        {
            documentType = EU_DOCType;
        }
    }
    else if(isXls)
    {
        documentType = EU_XLSType;
    }
    else if(isPpt)
    {
        documentType = EU_PPTType;
    }
    else
    {
        libolecf_item_t* packageItem = nullptr;
        if (hasOleTreeItem(intputItem, "Package", &packageItem, false, true))
        {
            if (packageItem)
            {
                QByteArray zipData = getOleItemData(packageItem);
                documentType = getPackage(zipData);
                haveOutput = true;
                *outputItem = packageItem;
            }
        }
    }

    if (documentType == EU_DocumentType::EU_NoType)
    {
        libolecf_item_t* ole10NativeItem = nullptr;
        if (hasOleTreeItem(intputItem, "Ole10Native", &ole10NativeItem, true, true))
        {
            if (ole10NativeItem)
            {
                documentType = EU_DocumentType::EU_BinType;
                haveOutput = true;
                *outputItem = ole10NativeItem;
            }
        }
    }

    return documentType;
}

QList<libolecf_item_t*> getXlsAttachmentLibOlecfItem(libolecf_item_t* inputRootItem)
{
    QList<libolecf_item_t*> tmpList;
    if (inputRootItem)
    {
        int subItemCount = 0;
        libolecf_item_get_number_of_sub_items(inputRootItem, &subItemCount, nullptr);
        for (int i = 0; i < subItemCount; ++i)
        {
            libolecf_item_t* subItem = nullptr;
            libolecf_item_get_sub_item(inputRootItem, i, &subItem, nullptr);
            QString nodeName = getOleItemName(subItem);
            if (nodeName.startsWith("MBD"))
            {
                tmpList.append(subItem);
            }
        }
    }
    return tmpList;
}

void outputFile(const QByteArray& data)
{
    QFile file("E:/test/newppt.stream");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
    }
}

QList<libolecf_item_t*> getDocAttachmentLibOlecfItem(libolecf_item_t* inputRootItem)
{
    QList<libolecf_item_t*> tmpList;
    if (inputRootItem)
    {
        tmpList = getXlsAttachmentLibOlecfItem(inputRootItem);
        int subItemCount = 0;
        libolecf_item_get_number_of_sub_items(inputRootItem, &subItemCount, nullptr);
        for (int i = 0; i < subItemCount; ++i)
        {
            libolecf_item_t* subItem = nullptr;
            libolecf_item_get_sub_item(inputRootItem, i, &subItem, nullptr);
            if (!subItem)
            {
                continue;
            }
            QString nodeName = getOleItemName(subItem);
            if (nodeName.startsWith("ObjectPool"))
            {
                int nObjectCount = 0;
                libolecf_item_get_number_of_sub_items(subItem, &nObjectCount, nullptr);
                for (int j = 0; j < nObjectCount; ++j)
                {
                    libolecf_item_t* objItem = nullptr;
                    libolecf_item_get_sub_item(subItem, j, &objItem, nullptr);
                    QString qsObjName = getOleItemName(objItem);
                    if (qsObjName.startsWith("_"))
                    {
                        tmpList.append(subItem);
                    }
                }
            }
        }
    }
    return tmpList;
}

QList<libolecf_item_t*> getPptAttachmentLibOlecfItem(libolecf_item_t* inputRootItem)
{
    const quint16 PPTContainer_Head = 0xF;
    const quint16 DocumentContainer = 0x03E8;
    // 读取 Pictures 流查找 xls
    libolecf_item_t* pictures = nullptr;

    QList<libolecf_item_t*> tmpList;
    if (inputRootItem)
    {
        int subItemCount = 0;
        libolecf_item_get_number_of_sub_items(inputRootItem, &subItemCount, nullptr);
        for (int i = 0; i < subItemCount; ++i)
        {
            libolecf_item_t* subItem = nullptr;
            libolecf_item_get_sub_item(inputRootItem, i, &subItem, nullptr);
            QString nodeName = getOleItemName(subItem);
            if (nodeName.startsWith("PowerPoint Document"))
            {
                //DocumentContainter
                QByteArray pptDocData = getOleItemData(subItem);
                QByteArray srcData = pptDocData;
                QByteArray otherData = pptDocData;
                int pos = 0;
                quint16 ftHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 2;
                quint16 ftType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 2;
                quint32 ftSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 4;
                pptDocData = pptDocData.mid(pos, ftSize);
                pos += ftSize;
                otherData = otherData.mid(pos, otherData.size() - pos);
                pos = 0;
                //DocumentAtom 
                quint16 atomHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 2;
                quint16 atomType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 2;
                quint32 atomSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 4;
                pos += atomSize;
                pptDocData = pptDocData.mid(pos, pptDocData.size() - pos);
                pos = 0;
                outputFile(pptDocData);
                //ExObjListContainer
                quint16 objListContainerHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 2;
                quint16 objListContainerType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 2;
                quint32 objListContainerSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(pptDocData.constData() + pos));
                pos += 4;
                QByteArray containerData = pptDocData.mid(pos, objListContainerSize);
                pos += objListContainerSize;
                pptDocData = pptDocData.mid(pos, pptDocData.size() - pos);
                pos = 0;
                outputFile(containerData);
                //objListAtom
                quint16 objListAtomHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint16 objListAtomType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint32 objListAtomSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 4;
               // QByteArray objListAtomData = containerData.mid(pos, objListAtomSize);
                pos += objListAtomSize;
                containerData = containerData.mid(pos, containerData.size() - pos);
                pos = 0;
                //ExObjListAtom
                

                outputFile(containerData);
                quint16 oleEmbedContainerHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint16 oleEmbedContainerType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint32 oleEmbedContainerSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 4;
                containerData = containerData.mid(pos, containerData.size() - pos);
                outputFile(containerData);
                pos = 0;
                quint16 oleEmbedAtomHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint16 oleEmbedAtomType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint32 oleEmbedAtomSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 4;
                pos += oleEmbedAtomSize;
                containerData = containerData.mid(pos, containerData.size() - pos);
                outputFile(containerData);
                pos = 0;
                quint16 oleObjAtomHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint16 oleObjAtomType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 2;
                quint32 oleObjAtomSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(containerData.constData() + pos));
                pos += 4;
                QByteArray oleObjAtomData = containerData.mid(pos, oleObjAtomSize);
                pos = 0;
                quint32 drawAspect = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(oleObjAtomData.constData() + pos));
                pos += 4;
                quint32 oleObjType = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(oleObjAtomData.constData() + pos));
                pos += 4;
                quint32 exObjId = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(oleObjAtomData.constData() + pos));
                pos += 4;
                quint32 subType = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(oleObjAtomData.constData() + pos));
                pos += 4;
                quint32 persistIdRef = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(oleObjAtomData.constData() + pos));
                pos = 0;

                quint16 wHead;// = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(otherData.constData() + pos));
                //pos += 2;
                quint16 wType;// = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(otherData.constData() + pos));
                //pos += 2;
                quint32 wSize;// = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(otherData.constData() + pos));
                //pos += 4;
                while (true)
                {
                    wHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(otherData.constData() + pos));
                    pos += 2;
                    wType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(otherData.constData() + pos));
                    pos += 2;
                    wSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(otherData.constData() + pos));
                    pos += 4;
                    

                    if (wType == 0x1772)
                    {
                        int tPos = 0;
                        QByteArray PersistDirectoryEntryData = otherData.mid(pos, otherData.size() - pos);
                        quint32 PersistBits = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(PersistDirectoryEntryData.constData() + tPos));
                        quint16 cPersist = PersistBits >> 20;
                        quint32 persistId = PersistBits & 0xFFFFF;
                        tPos += 4;

                        quint32 oneData = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(PersistDirectoryEntryData.constData() + tPos));
                        tPos += 4;
                        quint32 twoData = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(PersistDirectoryEntryData.constData() + tPos));
                        
                        QByteArray ID2OleObjMaybeData = srcData.mid(twoData, srcData.size() - twoData);
                        
                        outputFile(ID2OleObjMaybeData);

                        tPos = 0;
                        quint16 sHead = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ID2OleObjMaybeData.constData() + tPos));
                        tPos += 2;
                        quint16 sType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ID2OleObjMaybeData.constData() + tPos));
                        tPos += 2;

                        qDebug() << "========== 使用 inflate 手动解压 ==========";

                        // 读取值（和之前一样）
                        quint32 value1 = qFromLittleEndian<quint32>(
                            reinterpret_cast<const uchar*>(ID2OleObjMaybeData.constData() + tPos)
                            );
                        tPos += 4;
                        quint32 value2 = qFromLittleEndian<quint32>(
                            reinterpret_cast<const uchar*>(ID2OleObjMaybeData.constData() + tPos)
                            );
                        tPos += 4;

                        quint32 unSize = value2;  // 492544
                        quint32 sSize = value1;   // 481473

                        qDebug() << "unSize =" << unSize;
                        qDebug() << "sSize =" << sSize;

                        // 读取压缩数据
                        QByteArray compressedData = ID2OleObjMaybeData.mid(tPos, sSize);
                        qDebug() << u8"压缩数据大小:" << compressedData.size();
                        qDebug() << u8"压缩数据头:" << compressedData.left(16).toHex(' ');

                        // ========== 使用 inflate 流式解压 ==========
                        z_stream strm;
                        memset(&strm, 0, sizeof(strm));
                        strm.zalloc = Z_NULL;
                        strm.zfree = Z_NULL;
                        strm.opaque = Z_NULL;
                        strm.avail_in = compressedData.size();
                        strm.next_in = reinterpret_cast<Bytef*>(compressedData.data());

                        // 初始化（自动检测 zlib 或 deflate 格式）
                        int ret = inflateInit(&strm);
                        if (ret != Z_OK) {
                            qWarning() << u8"inflateInit 失败:" << ret;
                            //return;
                        }

                        // 准备输出缓冲区（给足够大的空间）
                        quint32 bufferSize = unSize;  // 多分配 100KB
                        QByteArray outPutData(bufferSize, 0);
                        strm.avail_out = bufferSize;
                        strm.next_out = reinterpret_cast<Bytef*>(outPutData.data());

                        qDebug() << u8"\n开始解压...";
                        qDebug() << u8"输入大小:" << strm.avail_in;
                        qDebug() << u8"输出缓冲区:" << bufferSize;

                        // 解压
                        ret = inflate(&strm, Z_FINISH);

                        if (strm.total_out == unSize)
                        {
                            outPutData.resize(strm.total_out);
                            QFile file("E:/test/partial.bin");
                            if (file.open(QIODevice::WriteOnly)) {
                                file.write(outPutData);
                                file.close();
                                qDebug() << u8"✓ 已保存部分数据 (" << strm.total_out << u8"字节) 到:"
                                    << file.fileName();
                            }
                        }
                        // 清理
                        inflateEnd(&strm);


                        //outputFile(datadd);
                       // QByteArray decompressed = qUncompress(datadd);
                        
                        break;
                    }
                    pos += wSize;
                    outputFile(otherData.mid(pos, otherData.size() - pos));
                } 
            }
        }
    }
    return tmpList;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QByteArray data;
   // QString qsETFilePath = "E:\\test\\indoc.et";
    //QString qsPPTFilePath = "E:\\test\\new.ppt";
    QString oleFile = "E:\\test\\partial.bin";
    libolecf_file_t* file = nullptr;
    libolecf_item_t* item = nullptr;
    libolecf_error_t* error = nullptr;

    // 打开文件
    libolecf_file_initialize(&file, &error);
    libolecf_file_open(file, oleFile.toUtf8().constData(),
        LIBOLECF_OPEN_READ, &error);

    libolecf_item_t* pRootIem = nullptr;
    libolecf_file_get_root_item(file, &pRootIem, &error);

    if (pRootIem)
    {
        bool haveOutPut = false;
        libolecf_item_t* tmpItem = nullptr;
        QList<libolecf_item_t*> oleItemList;
        EU_DocumentType docType = getOleFileFormat(pRootIem, haveOutPut, &tmpItem);
        if (docType == EU_DOCType || docType == EU_WPSType)
        {
            oleItemList = getDocAttachmentLibOlecfItem(pRootIem);
        }
        else if (docType == EU_XLSType || docType == EU_ETType)
        {
            oleItemList = getXlsAttachmentLibOlecfItem(pRootIem);
        }
        else if (docType == EU_PPTType || docType == EU_DPSType)
        {
            getPptAttachmentLibOlecfItem(pRootIem);
        }
        else if(docType == EU_BinType)
        {
            if (haveOutPut)
            {
                QByteArray oleData = getOleItemData(tmpItem);
                ST_VarantFile vFile;
                parseOle10Native(oleData, vFile);
                QFile file("E:/test/newppt.xls");
                if (file.open(QIODevice::WriteOnly))
                {
                    file.write(vFile.fileData);
                    file.close();
                }
            }
            
        }
        else
        {

        }

        for (int i = 0; i < oleItemList.count(); ++i)
        {
            libolecf_item_t* pItem = oleItemList.at(i);
            if (!pItem)
            {
                continue;
            }
            
        }
    }

    


    // 根据路径获取项
    // streamPath 格式如 "Workbook" 或 "Root Entry/Workbook"
    const QString streamPath = "Workbook";
    if (libolecf_file_get_item_by_utf8_path(
            file,
            (const uint8_t *)streamPath.toUtf8().constData(),
            streamPath.toUtf8().size(),
            &item,
            &error) == 1) 
    {

        // 读取流数据
        uint32_t stream_size = 0;
        libolecf_item_get_size(item, &stream_size, nullptr);

        //限制图片大小不超过100M防止内存过大
        if (stream_size > 0)
        {
            data.resize(stream_size);

            libolecf_stream_read_buffer(
                item,
                (uint8_t*)data.data(),
                stream_size,
                nullptr
                );
        }

        libolecf_item_free(&item, nullptr);
    }

    libolecf_file_close(file, nullptr);
    libolecf_file_free(&file, nullptr);


    auto readBIFF = [&](int& pos, QByteArray & srcData)->QPair<quint16, quint16> {
        BIFFHeadPair typeAndSizePair;
        typeAndSizePair.first = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(srcData.constData() + pos));
        typeAndSizePair.second = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(srcData.constData() + pos + 2));
        pos = pos + 4;
        return typeAndSizePair;
    };
    auto readLOGIC = [&](int& pos, quint16 & head, QByteArray& srcData)->QPair<quint16, quint32> {
        LogicHeadPair typeAndSizePair;
        head = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(srcData.constData() + pos));
        typeAndSizePair.first = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(srcData.constData() + pos + 2));
        typeAndSizePair.second = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(srcData.constData() + pos + 4));
        pos = pos + 8;
        return typeAndSizePair;
    };


    std::function<void(const QByteArray&, int, int, int&)> parseOfficeArt;
    parseOfficeArt = [&](const QByteArray& data, int start, int end, int& count) {
        int pos = start;
        while (pos + 8 <= end) {
            const uchar* p = (uchar*)data.constData() + pos;

            quint16 verInst = qFromLittleEndian<quint16>(p);
            quint16 type = qFromLittleEndian<quint16>(p + 2);
            quint32 length = qFromLittleEndian<quint32>(p + 4);

            qDebug() << QString("pos=%1, type=0x%2, length=%3, verInst=0x%4")
                .arg(pos).arg(type, 4, 16, QChar('0'))
                .arg(length).arg(verInst, 4, 16, QChar('0'));

            if (type == OfficeArtClientData) {
                count++;
                qDebug() << "Found ClientData!";
            }

            // 判断是否为容器：verInst 的低4位为 0xF
            bool isContainer = (verInst & 0x000F) == 0x000F;

            if (isContainer && length > 0) {
                // 递归解析容器内容
                qDebug() << "  -> Entering container";
                parseOfficeArt(data, pos + 8, pos + 8 + length, count);
            }

            pos += 8 + length;
        }
    };

    int off = 0;
    bool isContinueData = false;
    while (off + 4 <= data.size()) //BIFF while
    {
        QPair<quint16, quint16> biffPair = readBIFF(off, data);
        if (off + biffPair.second > data.size()) break;

        if (biffPair.first == EU_XLSReordType::MsoDrawingReordType)//只查附件
        {
            QByteArray drawingData;
            quint16 headData = 0;
            int logicPos = off;
            LogicHeadPair logicDataPair = readLOGIC(logicPos, headData, data);
            if (headData == Container_Header)
            {
                quint32 diffDataSize = logicDataPair.second - (biffPair.second - 8);
                if (true)
                {
                    do
                    {
                        drawingData.append(data.mid(off, biffPair.second));
                        off += biffPair.second;
                        biffPair = readBIFF(off, data);
                        if (off + biffPair.second > data.size())
                        {
                            qDebug() << u8"数据不足";
                            break;
                        }
                    } while (biffPair.first == EU_ContinueType::REC_MSODRAWING_CONT || biffPair.first == EU_ContinueType::REC_MSODRAWING_CONT2);


                    int count = 0;
                    parseOfficeArt(drawingData, 0, drawingData.size(), count);

                    for (int i = 0; i < count; ++i)
                    {
                        if (biffPair.first == EU_XLSReordType::ObjReordType)
                        {
                            int objPos = 0;
                            QByteArray objBa = data.mid(off, biffPair.second);
                            quint16 ftData = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(objBa.constData() + objPos));
                            quint16 cbData = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(objBa.constData() + objPos + 2));
                            quint16 otData = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(objBa.constData() + objPos + 4));
                            quint16 idData = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(objBa.constData() + objPos + 6));
                            
                            off += biffPair.second;
                            if (off > data.size())
                            {
                                break;
                            }
                            biffPair = readBIFF(off, data);
                        }
                        else
                        {
                            break;
                            
                        }
                    }
                  
                    /*QFile file("E:/projectGita/xlsfileparser/drawing2.bin");
                    if (file.open(QIODevice::WriteOnly))
                    {
                        file.write(tmpData);
                        file.close();
                    }*/
                }               
            }
        }
        else if(biffPair.first == EU_ContinueType::REC_MSODRAWING_CONT || biffPair.first == EU_ContinueType::REC_MSODRAWING_CONT2)
        {

        }
        else
        {

        }
        
        off += biffPair.second;// 下一条记录
    }


    MainWindow w;
    w.show();
    return a.exec();
}
