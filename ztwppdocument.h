#ifndef ZTWPPDOCUMENT_H
#define ZTWPPDOCUMENT_H

#include "zttools.h"

struct ST_Datablock
{
    quint32 startPos = 0;
    quint32 endPos = 0;
};

class ZTWPPDocument
{
    enum HeaderType
    {
        RT_Document = 0x03E8,
        RT_DocumentAtom = 0x03E9,
        RT_Slide = 0x03EE,
        RT_SlideAtom = 0x03EF,
        RT_ExternalObjectList = 0x0409,
        RT_ExternalObjectListAtom = 0x040A,
        RT_Environment = 0x03F2,
        RT_SoundCollection = 0x07E4,
        RT_DrawingGroup = 0x040B,

        RT_ExternalAviMovie = 0x1006,
        RT_ExternalCdAudio = 0x100E,
        RT_ExternalOleControl = 0x0FEE,
        RT_ExternalHyperlink = 0x0FD7,
        RT_ExternalMciMovie = 0x1007,
        RT_ExternalMidiAudio = 0x100D,
        RT_ExternalOleEmbed = 0x0FCC,
        RT_ExternalOleLink = 0x0FCE,
        RT_ExternalWavAudioEmbedded = 0x100F,
        RT_ExternalWavAudioLink = 0x1010,



        RT_ExternalOleEmbedAtom = 0x0FCD,
        RT_ExternalOleObjectAtom = 0x0FC3,

        RT_MainMaster = 0x03F8,
        RT_ExternalOleObjectStg = 0x1011,
        RT_PersistDirectoryAtom = 0x1772

    };
public:
    ZTWPPDocument();

    bool openWPPFile(const QString& qsFilePath);

    bool readPPTData();

    void parserData();
protected:
    quint32 parserDocument();

    quint32 parserDocumentAtom(quint32 pos);

    quint32 parserExObjList(quint32 pos);

    quint32 parserExObjListAtom(quint32 pos, quint32 &count);

    void parserExObjListSubContainer(quint32 pos, quint32 exObjCount);

    void parserExOleEmbedContainer(quint32 pos);

    bool parserPersistDirectoryAtom(quint32 idRef);

    int extratorAttachment(quint32 pos);

    quint32 parserDocumentTextInfoContainer(quint32 pos);

    quint32 paserSoundCollection(quint32 pos);

    quint32 paserDrawingGroup(quint32 pos);
private:

    bool physicalStruct(quint32 pos, quint16& ftHead, quint16& ftType, quint32& ftSize, quint32& startPos, quint32& endPos);

    quint16 getPhysicalStructType(quint32 pos);

    QList<QPair<quint16, quint32> > findType(HeaderType headType);

    bool oleAttachmentSecondParser(const QString& qsFilePath, ST_VarantFile& varantFile);

    bool oleAttachmentSecondParser(const QByteArray& oleData);
    //quint64 getOffsetTypeID(quint32 offset, quint16 type);
    //
    //quint32 getType(quint64 offsetID);

    //quint32 getOffset(quint64 offsetID);

private:
    QSharedPointer<libolecf_file_t> m_oleFilePtr;
    QSharedPointer<libolecf_item_t> m_pRootIemPtr;
    QList<QByteArray> m_slideDataList;
    QByteArray m_srcData;
    QList<QPair<quint16, quint32> > m_typeOffsetList;
};

#endif // ZTWPPDOCUMENT_H
