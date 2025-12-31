#ifndef ZTTOOLS_H
#define ZTTOOLS_H

#include "global.h"

void oleItemDeleter(libolecf_item_t* item);

void oleFileDeleter(libolecf_file_t *file);

void oleErrorDeleter(libolecf_error_t *oleError);

int ZT_libolecf_item_get_sub_item(const QSharedPointer<libolecf_item_t>& parentItem, int num, QSharedPointer<libolecf_item_t> &subItem, QSharedPointer<libolecf_error_t>& error);

int ZT_libolecf_item_get_sub_item_by_utf8_path(const QSharedPointer<libolecf_item_t>& item,
                                               const uint8_t *utf8_string,
                                               size_t utf8_string_length,
                                               QSharedPointer<libolecf_item_t> &subItem,
                                               QSharedPointer<libolecf_error_t>& error);
class ZTTools
{
    static bool parseOle10Native(const QByteArray& ole10NativeData, ST_VarantFile& stOleFile);

    EU_DocumentType getZipPackage(const QByteArray& zipBytes);//查看内部结构是不是docx等

    bool findOleTreeItem(QSharedPointer<libolecf_item_t> intputItem, const QString& nodeName, QSharedPointer<libolecf_item_t>& subItem, bool isRegex = false, bool isOutPut = false);
public:

    ZTTools();
};

#endif // ZTTOOLS_H
