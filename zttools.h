#ifndef ZTTOOLS_H
#define ZTTOOLS_H

#include "global.h"

void oleItemDeleter(libolecf_item_t* item);

void oleFileDeleter(libolecf_file_t *file);

void oleErrorDeleter(libolecf_error_t *oleError);

int ZT_libolecf_item_get_sub_item(const QSharedPointer<libolecf_item_t>& parentItem, int num, QSharedPointer<libolecf_item_t> &subItem, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_item_get_sub_item_by_utf8_path(const QSharedPointer<libolecf_item_t>& item,
                                               const uint8_t *utf8_string,
                                               size_t utf8_string_length,
                                               QSharedPointer<libolecf_item_t> &subItem,
                                               QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_file_initialize(QSharedPointer<libolecf_file_t> &file, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_file_open(const QSharedPointer<libolecf_file_t>& file, const char* filename, int access_flags, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_item_get_number_of_sub_items(const QSharedPointer<libolecf_item_t>& oleItem, int &count, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_item_get_utf8_name_size(const QSharedPointer<libolecf_item_t>& oleItem, size_t * utf8_string_size, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_item_get_utf8_name(const QSharedPointer<libolecf_item_t>& oleItem, uint8_t* utf8_string, const size_t& utf8_string_size, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_item_get_size(const QSharedPointer<libolecf_item_t>& item, uint32_t* size, QSharedPointer<libolecf_error_t>* error = nullptr);

int ZT_libolecf_stream_read_buffer(const QSharedPointer<libolecf_item_t>& intputItem, uint8_t* buffer, const size_t& size, QSharedPointer<libolecf_error_t>* error = nullptr);
class ZTTools
{
    static bool parseOle10Native(const QByteArray& ole10NativeData, ST_VarantFile& stOleFile);

    EU_DocumentType getOleFileFormat(const QSharedPointer<libolecf_item_t>& intputItem, bool& haveOutput, QSharedPointer<libolecf_item_t>& outputItem);

    static EU_DocumentType getZipPackage(const QByteArray& zipBytes);//查看内部结构是不是docx等

    static bool findOleTreeItem(const QSharedPointer<libolecf_item_t>& intputItem, const QString& nodeName, QSharedPointer<libolecf_item_t>& subItem, bool isRegex = false, bool isOutPut = false);

    static QString getOleItemName(const QSharedPointer<libolecf_item_t>& pItem);

    static QByteArray getOleItemData(const QSharedPointer<libolecf_item_t>& intputItem);
public:

    ZTTools();
};

#endif // ZTTOOLS_H
