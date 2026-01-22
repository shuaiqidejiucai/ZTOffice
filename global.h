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
    quint32 originPos = 0;
    quint32 ftSize = 0;
    quint16 ftType = 0;
    
    quint16 recVer : 4;
    quint16 recInstance : 12;
    //bool isValid;
};

struct PointStruct
{
    qint32 x = 0;
    qint32 y = 0;
};

struct RatioStruct
{
    qint32 numer = 0;
    qint32 denom = 0;
};

#define ST_SP(var)      ((var).startPos)
#define ST_EP(var)      ((var).endPos)
#define ST_OP(var)      ((var).originPos)
#define ST_SZ(var)      ((var).ftSize)
#define ST_TP(var)      ((var).ftType)

#define ST_RV(var)      ((var).recVer)
#define ST_RI(var)      ((var).recInstance)
//#define ST_VL(var)      ((var).isValid)
#endif // GLOBAL_H
