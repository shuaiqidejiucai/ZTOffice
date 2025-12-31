#include "zttools.h"


bool ZTTools::parseOle10Native(const QByteArray &ole10NativeData, ST_VarantFile &stOleFile)
{
    if (ole10NativeData.size() < 12) return false;

    int offset = 0;

    // 1. totalSize
    quint32 totalSize = qFromLittleEndian<quint32>(
        reinterpret_cast<const uchar*>(ole10NativeData.constData() + offset)
        );
    offset += 4;

    // 2. signature/flags1
    quint16 signature = qFromLittleEndian<quint16>(
        reinterpret_cast<const uchar*>(ole10NativeData.constData() + offset)
        );
    offset += 2;

    QTextCodec* gbkCodec = QTextCodec::codecForName("GBK");

    if (signature == 0x0002) {
        // ===== Apache POI 的启发式判断 =====
        uchar firstByte = (offset < ole10NativeData.size()) ? static_cast<uchar>(ole10NativeData[offset]) : 0;

        if (firstByte > 0 && firstByte < 32) {
            // Compact 模式：label 的第一个字节是控制字符
            int dataSize = totalSize - 2;  // 减去 signature
            if (offset + dataSize <= ole10NativeData.size()) {
                stOleFile.fileData = ole10NativeData.mid(offset, dataSize);
                return true;
            }
        }
        else {
            // Parsed 模式：标准格式

            // ===== LibreOffice 的字符串跳过策略 =====
            auto skipNullTerm = [&]() -> QByteArray {
                int start = offset;
                while (offset < ole10NativeData.size() && ole10NativeData[offset] != '\0') ++offset;
                QByteArray result = ole10NativeData.mid(start, offset - start);
                if (offset < ole10NativeData.size()) ++offset;  // 跳过 '\0'
                return result;
            };

            // label
            QByteArray label = skipNullTerm();
            stOleFile.qsFileName = gbkCodec->toUnicode(label);

            // fileName
            QByteArray fileName = skipNullTerm();
            stOleFile.qsFilePath = gbkCodec->toUnicode(fileName);

            // 尝试读取可选的 flags2 + unknown1 (4 bytes)
            if (offset + 4 <= ole10NativeData.size()) {
                offset += 4;
            }

            // 尝试读取可选的 command（带长度前缀）
            if (offset + 4 <= ole10NativeData.size()) {
                quint32 commandLen = qFromLittleEndian<quint32>(
                    reinterpret_cast<const uchar*>(ole10NativeData.constData() + offset)
                    );
                if (commandLen > 0 && commandLen < 1024 &&
                    offset + 4 + commandLen <= ole10NativeData.size()) {
                    offset += 4 + commandLen;
                }
            }

            // dataSize
            if (offset + 4 <= ole10NativeData.size()) {
                quint32 dataSize = qFromLittleEndian<quint32>(
                    reinterpret_cast<const uchar*>(ole10NativeData.constData() + offset)
                    );
                offset += 4;

                if (offset + dataSize <= ole10NativeData.size()) {
                    stOleFile.fileData = ole10NativeData.mid(offset, dataSize);
                    return true;
                }
            }
        }
    }

    // ===== Unparsed 模式（兜底）=====
    // 从当前位置读取到 totalSize 指定的末尾
    int expectedEnd = 4 + totalSize;
    int remainingSize = expectedEnd - offset;
    if (remainingSize > 0 && offset + remainingSize <= ole10NativeData.size()) {
        stOleFile.fileData = ole10NativeData.mid(offset, remainingSize);
        return true;
    }

    return false;
}

EU_DocumentType ZTTools::getZipPackage(const QByteArray &zipBytes)
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

bool ZTTools::findOleTreeItem(QSharedPointer<libolecf_item_t> intputItem, const QString& nodeName, QSharedPointer<libolecf_item_t>& subItem, bool isRegex, bool isOutPut)
{
    if (isRegex)
    {
        int nItemCount = 0;
        libolecf_item_get_number_of_sub_items(intputItem.data(), &nItemCount, nullptr);

        for (int i = 0; i < nItemCount; ++i)
        {
            libolecf_item_t* subTmpItem = nullptr;
            libolecf_item_get_sub_item(intputItem.data(), i, &subTmpItem, nullptr);
            QSharedPointer<libolecf_item_t> p;

            libolecf_item_get_sub_item(intputItem.data(), i, &p.get(), nullptr);

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

ZTTools::ZTTools() {}



int ZT_libolecf_item_get_sub_item(const QSharedPointer<libolecf_item_t> &parentItem, int num, QSharedPointer<libolecf_item_t> &subItem, QSharedPointer<libolecf_error_t> &error)
{
    libolecf_item_t* rawItem = nullptr;
    libolecf_error_t* rawError = nullptr;
    int errorCode = libolecf_item_get_sub_item(parentItem.data(), num, &subItem, &rawError);
    if (rawItem) {
        subItem = QSharedPointer<libolecf_item_t>(rawItem, oleItemDeleter);
    }

    if (rawError) {
        error = QSharedPointer<libolecf_error_t>(rawError, oleErrorDeleter);
    }

    return errorCode;
}

void oleItemDeleter(libolecf_item_t *item)
{
    if (item)
    {
        libolecf_item_free(&item, nullptr);
    }
}

void oleFileDeleter(libolecf_file_t *file)
{
    if (file)
    {
        libolecf_file_close(file, nullptr);
        libolecf_file_free(&file, nullptr);
    }
}

void oleErrorDeleter(libolecf_error_t *oleError)
{
    if(oleError)
    {
        libolecf_error_free(&oleError);
    }
}

int ZT_libolecf_item_get_sub_item_by_utf8_path(const QSharedPointer<libolecf_item_t> &item, const uint8_t *utf8_string, size_t utf8_string_length, QSharedPointer<libolecf_item_t> &subItem, QSharedPointer<libolecf_error_t> &error)
{
    libolecf_item_t* rawItem = nullptr;
    libolecf_error_t * oleError = nullptr;
    int errorCode = libolecf_item_get_sub_item_by_utf8_path(item.data(), utf8_string, utf8_string_length, &rawItem, &oleError);
    if(rawItem)
    {
        subItem = QSharedPointer<libolecf_item_t>(rawItem, oleItemDeleter);
    }
    if(oleError)
    {
        error = QSharedPointer<libolecf_error_t>(error, oleErrorDeleter);
    }
    return errorCode;
}
