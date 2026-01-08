#include "mainwindow.h"
#include "global.h"
#include <QApplication>
#include "libolecf.h"
#include <qendian.h>
#include <QFile>
#include <QPair>
#include <qdebug.h>
#include <QStringList>
#include "zlib.h"
#include "qunzip/include/quazip.h"
#include <qbuffer.h>
#include <qtextcodec.h>
#include "ztwppdocument.h"


enum EU_ContinueType
{
    REC_MSODRAWING_CONT = 0x00EC,
    REC_MSODRAWING_CONT2 = 0x003C /*或 0x003C 视版本*/
};

const QString DOCXCLSID = "{F4754C9B-64F5-4B40-8AF4-679732AC0607}";
const QString XlSXCLSID = "{F4754C9B-64F5-4B40-8AF4-679732AC0607}";//占位
const QString PPTXCLSID = "{F4754C9B-64F5-4B40-8AF4-679732AC0607}";//占位


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



//
//QList<libolecf_item_t*> getXlsAttachmentLibOlecfItem(libolecf_item_t* inputRootItem)
//{
//    QList<libolecf_item_t*> tmpList;
//    if (inputRootItem)
//    {
//        int subItemCount = 0;
//        libolecf_item_get_number_of_sub_items(inputRootItem, &subItemCount, nullptr);
//        for (int i = 0; i < subItemCount; ++i)
//        {
//            libolecf_item_t* subItem = nullptr;
//            libolecf_item_get_sub_item(inputRootItem, i, &subItem, nullptr);
//            QString nodeName = getOleItemName(subItem);
//            if (nodeName.startsWith("MBD"))
//            {
//                tmpList.append(subItem);
//            }
//        }
//    }
//    return tmpList;
//}

//void outputFile(const QByteArray& data)
//{
//    QFile file("E:/test/newppt.stream");
//    if (file.open(QIODevice::WriteOnly))
//    {
//        file.write(data);
//        file.close();
//    }
//}
//
//QList<libolecf_item_t*> getDocAttachmentLibOlecfItem(libolecf_item_t* inputRootItem)
//{
//    QList<libolecf_item_t*> tmpList;
//    if (inputRootItem)
//    {
//        tmpList = getXlsAttachmentLibOlecfItem(inputRootItem);
//        int subItemCount = 0;
//        libolecf_item_get_number_of_sub_items(inputRootItem, &subItemCount, nullptr);
//        for (int i = 0; i < subItemCount; ++i)
//        {
//            libolecf_item_t* subItem = nullptr;
//            libolecf_item_get_sub_item(inputRootItem, i, &subItem, nullptr);
//            if (!subItem)
//            {
//                continue;
//            }
//            QString nodeName = getOleItemName(subItem);
//            if (nodeName.startsWith("ObjectPool"))
//            {
//                int nObjectCount = 0;
//                libolecf_item_get_number_of_sub_items(subItem, &nObjectCount, nullptr);
//                for (int j = 0; j < nObjectCount; ++j)
//                {
//                    libolecf_item_t* objItem = nullptr;
//                    libolecf_item_get_sub_item(subItem, j, &objItem, nullptr);
//                    QString qsObjName = getOleItemName(objItem);
//                    if (qsObjName.startsWith("_"))
//                    {
//                        tmpList.append(subItem);
//                    }
//                }
//            }
//        }
//    }
//    return tmpList;
//}


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QByteArray data;
    // QString qsETFilePath = "E:\\test\\indoc.et";
    QString qsPPTFilePath = "E:\\test\\new.ppt";

    ZTWPPDocument wk;
    wk.openWPPFile(qsPPTFilePath);
    wk.readPPTData();
    wk.parserData();



    MainWindow w;
    w.show();
    return a.exec();
}
