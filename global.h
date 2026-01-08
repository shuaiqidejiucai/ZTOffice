#ifndef GLOBAL_H
#define GLOBAL_H

#include "libolecf.h"
#include <qsharedpointer.h>
#include <qendian.h>
#include <QFile>
#include <QPair>
#include <qdebug.h>
#include <QStringList>
#include <qbuffer.h>
#include "zlib.h"
#include "qunzip/include/quazip.h"
#include <qtextcodec.h>
#include <qbytearray.h>
#include <QString>
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
    QString qsSuffix;//AS:.zip
    QString qsBaseName;//AS:temp
    QString qsTmpFilePath;//AS:C:/user/temp/temp.zip
    QString qsFilePath;//AS:D:/test/temp.zip
    QByteArray fileData;//AS:zip data
};

#endif // GLOBAL_H
