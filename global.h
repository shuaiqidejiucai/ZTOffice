#ifndef GLOBAL_H
#define GLOBAL_H

#include "libolecf.h"
#include <qsharedpointer.h>
enum EU_DocumentType
{
    EU_NoType,
    EU_DOCType,
    EU_DOCXType,
    EU_WPSType,
    EU_XLSType,
    EU_XLSXType,
    EU_ETType,
    EU_PPTType,
    EU_PPTXType,
    EU_DPSType,
    EU_BinType
};

struct ST_VarantFile
{
    QString qsFileName;//AS:temp.zip
    QString qsTmpFilePath;//AS:C:/user/temp/temp.zip
    QString qsFilePath;//AS:D:/test/temp.zip
    QByteArray fileData;//AS:zip data
};

#endif // GLOBAL_H
