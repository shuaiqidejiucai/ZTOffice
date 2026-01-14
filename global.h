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

struct ST_Variable
{
    quint32 startPos = 0;
    quint32 endPos = 0;
    quint32 srcPos = 0;
    quint32 ftSize = 0;
    quint16 ftHead = 0;
    quint16 ftType = 0;
    bool isValid;
};
#define VT_SIZE(var)        ((var).ftSize)
#define VT_SRCPOS(var)      ((var).srcPos)
#define VT_STARTPOS(var)    ((var).startPos)
#define VT_ENDPOS(var)      ((var).endPos)
#define VT_HEAD(var)        ((var).ftHead)
#define VT_TYPE(var)        ((var).ftType)
#define VT_VALID(var)       ((var).isValid)
#endif // GLOBAL_H
