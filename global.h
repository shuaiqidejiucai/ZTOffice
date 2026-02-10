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


#include <QtCore/qglobal.h>

#if defined(PSTParser_LIBRARY)
#define PSTParser_EXPORT Q_DECL_EXPORT
#else
#define PSTParser_EXPORT Q_DECL_IMPORT
#endif

enum EU_ErrorCodeType
{
    Error_FailedType = -1,
    Error_SuccessType,
    Error_ExternalParserType,//因无识别头所以由构造者解析出数据
    Error_BinType,//无特别成员数据，纯二进制流，如：附件流、文字流、图片流等，无需解析有位置即可，位置是判断类型时，构造者赋予的
    Error_TODO //待完成
};

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
    ST_Variable() 
        :startPos(0)
        , endPos(0)
        , originPos(0)
        , ftSize(0)
        , ftType(0)
        , recVer(0)
        , recInstance(0)
    {

    }
    quint32 startPos;
    quint32 endPos;
    quint32 originPos;
    quint32 ftSize;
    quint16 ftType;
    
    quint16 recVer;
    quint16 recInstance;

    void initStruct()
    {
        startPos = 0;
        endPos = 0;
        originPos = 0;
        ftSize = 0;
        ftType = 0;

        recVer = 0;
        recInstance = 0;
    }
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
