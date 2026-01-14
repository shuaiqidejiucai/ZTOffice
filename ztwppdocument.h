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
    enum PersistDirectoryType
    {
        TextType,
        AttachmentType,
        ImageType
    };

    enum HeaderType
    {
        RT_Document = 0x03E8,
        RT_DocumentAtom = 0x03E9,

        RT_SlideAtom = 0x03EF,
        RT_ExternalObjectList = 0x0409,
        RT_ExternalObjectListAtom = 0x040A,
        RT_Environment = 0x03F2,
        RT_SoundCollection = 0x07E4,
        RT_DrawingGroup = 0x040B,
        RT_SlideListWithText = 0x0FF0,
        RT_List = 0x07D0,
        RT_HeadersFooters = 0x0FD9,
        RT_SlideShowDocInfoAtom = 0x0401,
        RT_NamedShows = 0x0410,
        RT_Summary = 0x0402,
        RT_DocRoutingSlipAtom = 0x0406,
        RT_PrintOptionsAtom = 0x1770,
        RT_Drawing = 0x040C,

        
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
        RT_SlidePersistAtom = 0x03F3,
        RT_TextHeaderAtom = 0x0F9F,
        RT_TextCharsAtom = 0x0FA0,
        RT_TextBytesAtom = 0x0FA8,
        RT_StyleTextPropAtom = 0x0FA1,
        RT_SlideNumberMetaCharAtom = 0x0FD8,
        RT_DateTimeMetaCharAtom = 0x0FF7,
        RT_GenericDateMetaCharAtom = 0x0FF8,
        RT_HeaderMetaCharAtom = 0x0FF9,
        RT_FooterMetaCharAtom = 0x0FFA,
        RT_RtfDateTimeMetaCharAtom = 0x1015,
        RT_TextBookmarkAtom = 0x0FA7,
        RT_TextSpecialInfoAtom = 0x0FAA,
        RT_InteractiveInfo = 0x0FF2,
        RT_TextInteractiveInfoAtom = 0x0FDF,
        RT_SlideShowSlideInfoAtom = 0x03F9,
        RT_RoundTripSlideSyncInfo12 = 0x3714,
        RT_RoundTripSlideSyncInfoAtom12 = 0x3715,
        RT_ColorSchemeAtom = 0x07F0,
        RT_RoundTripTheme12Atom = 0x040E,
        RT_RoundTripColorMapping12Atom = 0x040F,
        RT_RoundTripCompositeMasterId12Atom = 0x041D,
        RT_RoundTripContentMasterInfo12Atom = 0x041E,
        RT_RoundTripAnimationHashAtom12Atom = 0x2B0D,
        RT_RoundTripAnimationAtom12Atom = 0x2B0B,
        RT_RoundTripContentMasterId12Atom = 0x0422,

        RT_ProgTags = 0x1388,
        RT_NormalViewSetInfo9 = 0x0414,
        RT_NotesTextViewInfo9 = 0x0413,
        RT_OutlineViewInfo = 0x0407,
        RT_SlideViewInfo = 0x03FA,
        RT_SorterViewInfo = 0x0408,
        RT_VbaInfo = 0x03FF,

        RT_MainMaster = 0x03F8,
        RT_ExternalOleObjectStg = 0x1011,
        RT_Slide = 0x03EE,
        RT_Notes = 0x03F0,
        RT_Handout = 0x0FC9,

        RT_CString = 0x0FBA,


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

    quint32 parserExObjListAtom(quint32 pos);

    void parserExObjListSubContainer(quint32 pos);

    void parserExOleEmbedContainer(quint32 pos);

    bool parserPersistDirectoryAtom(quint32 idRef, PersistDirectoryType type = AttachmentType);

    int extratorAttachment(quint32 pos);

    int extratorText(quint32 pos);

    quint32 parserDocumentTextInfoContainer(quint32 pos);

    quint32 parserSoundCollection(quint32 pos);

    quint32 parserDrawingGroup(quint32 pos);

    quint32 parserMasterList(quint32 pos);

    quint32 parserDocInfoList(quint32 pos);

    quint32 parserSlideHF(quint32 pos);

    quint32 parserNotesHF(quint32 pos);

    quint32 parserSlideList(quint32 pos);

    quint32 parserSlideListWithTextSubContainerOrAtom(quint32 pos);

    quint32 parserNotesList(quint32 pos);

    quint32 parserSlideShowDocInfoAtom(quint32 pos);

    quint32 parserNamedShows(quint32 pos);

    quint32 parserSummary(quint32 pos);

    quint32 parserDocRoutingSlipAtom(quint32 pos);

    quint32 parserPrintOptionsAtom(quint32 pos);

    quint32 parserDocInfoListContainer(quint32 pos);

    quint32 parserPerSlideHeadersFootersContainer(quint32 pos);
    
    void parserSlide(quint32 pos);
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
