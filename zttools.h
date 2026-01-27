#ifndef ZTTOOLS_H
#define ZTTOOLS_H

#include "global.h"

enum HeaderType
{
    RT_Document = 0x03E8,
    RT_DocumentAtom = 0x03E9,
    RT_EndDocumentAtom = 0x03EA,
    RT_SlideAtom = 0x03EF,
    RT_ExternalObjectList = 0x0409,
    RT_ExternalObjectListAtom = 0x040A,
    RT_Environment = 0x03F2,
    RT_FontCollection = 0x07D5,
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


    RT_Kinsoku = 0x0FC8,
    RT_ExternalOleEmbedAtom = 0x0FCD,
    RT_ExternalOleObjectAtom = 0x0FC3,
    RT_SlidePersistAtom = 0x03F3,
    RT_TextHeaderAtom = 0x0F9F,
    RT_TextCharsAtom = 0x0FA0,
    RT_TextCharFormatExceptionAtom = 0x0FA4,
    RT_TextParagraphFormatExceptionAtom = 0x0FA5,
    RT_TextBytesAtom = 0x0FA8,
    RT_TextSpecialInfoDefaultAtom = 0x0FA9,
    RT_StyleTextPropAtom = 0x0FA1,
    RT_TextMasterStyleAtom = 0x0FA3,
    RT_FontEntityAtom = 0x0FB7,
    RT_KinsokuAtom = 0x0FD2,
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
    RT_ProgBinaryTag = 0x138A,
    RT_BinaryTagDataBlob = 0x138B,
    RT_NormalViewSetInfo9 = 0x0414,
    RT_NormalViewSetInfo9Atom = 0x0415,
    RT_ViewInfoAtom = 0x03FD,
    RT_SlideViewInfoAtom = 0x03FE,
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

    RT_HeadersFootersAtom = 0x0FDA,
    RT_PersistDirectoryAtom = 0x1772,
    RT_GridSpacing10Atom = 0x040D,
    RT_RoundTripCustomTableStyles12Atom = 0x0428,
    RT_RoundTripHeaderFooterDefaults12Atom = 0x0424,
    RT_RoundTripDocFlags12Atom = 0x0425,
    RT_SlideTime10Atom = 0x2EEB,

    //通用
    COMMON_OfficeArtDggContainer = 0xF000,
    COMMON_OfficeArtBStoreContainer = 0xF001,
    COMMON_OfficeArtFDGGBlock = 0xF006,
    COMMON_OfficeArtFBSE = 0xF007,
    COMMON_OfficeArtFOPT = 0xF00B,
    COMMON_OfficeArtSplitMenuColorContainer = 0xF11E
    
};

namespace ZT_Libolecf {
    void oleItemDeleter(libolecf_item_t* item);

    void oleFileDeleter(libolecf_file_t* file);

    void oleErrorDeleter(libolecf_error_t* oleError);

    int ZT_libolecf_item_get_sub_item(const QSharedPointer<libolecf_item_t>& parentItem, int num, QSharedPointer<libolecf_item_t>& subItem, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_item_get_sub_item_by_utf8_path(const QSharedPointer<libolecf_item_t>& item,
        const uint8_t* utf8_string,
        size_t utf8_string_length,
        QSharedPointer<libolecf_item_t>& subItem,
        QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_file_initialize(QSharedPointer<libolecf_file_t>& file, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_file_open(const QSharedPointer<libolecf_file_t>& file, const char* filename, int access_flags, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_item_get_number_of_sub_items(const QSharedPointer<libolecf_item_t>& oleItem, int& count, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_item_get_utf8_name_size(const QSharedPointer<libolecf_item_t>& oleItem, size_t* utf8_string_size, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_item_get_utf8_name(const QSharedPointer<libolecf_item_t>& oleItem, uint8_t* utf8_string, const size_t& utf8_string_size, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_item_get_size(const QSharedPointer<libolecf_item_t>& item, uint32_t* size, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_stream_read_buffer(const QSharedPointer<libolecf_item_t>& intputItem, uint8_t* buffer, const size_t& size, QSharedPointer<libolecf_error_t>* error = nullptr);

    int ZT_libolecf_file_get_root_item(const QSharedPointer<libolecf_file_t>& file, QSharedPointer<libolecf_item_t>& pRootIem, QSharedPointer<libolecf_error_t>* error = nullptr);

}

class ZTTools
{
public:

    static bool parseOle10Native(const QByteArray& ole10NativeData, ST_VarantFile& stOleFile);

    static EU_DocumentType getOleFileFormat(const QSharedPointer<libolecf_item_t>& intputItem, bool& haveOutput, QSharedPointer<libolecf_item_t>& outputItem);

    static EU_DocumentType getZipPackage(const QByteArray& zipBytes);//查看内部结构是不是docx等

    static bool findOleTreeItem(const QSharedPointer<libolecf_item_t>& intputItem, const QString& nodeName, QSharedPointer<libolecf_item_t>& subItem, bool isRegex = false, bool isOutPut = false);

    static QString getOleItemName(const QSharedPointer<libolecf_item_t>& pItem);

    static QByteArray getOleItemData(const QSharedPointer<libolecf_item_t>& intputItem);


    ZTTools();
};

template<class T>
inline T GetFlagData(const char* srcData, quint32 &pos)
{
    T data = qFromLittleEndian<T>(reinterpret_cast<const uchar*>(srcData + pos));
    pos += sizeof(T);
    return data;
}

inline bool physicalStruct(quint32 pos, const QByteArray& srcData, ST_Variable& stVar)
{
    if (pos + 8 < srcData.size())
    {
        stVar.originPos = pos;
        quint16 head = GetFlagData<quint16>(srcData.constData(), pos);
        ST_TP(stVar) = GetFlagData<quint16>(srcData.constData(), pos);
        ST_SZ(stVar) = GetFlagData<quint32>(srcData.constData(), pos);

        ST_RV(stVar) = head & 0xF;
        ST_RI(stVar) = head >> 4;
        if (pos + ST_SZ(stVar) < srcData.size())
        {
            ST_SP(stVar) = pos;
            ST_EP(stVar) = pos + ST_SZ(stVar);
            return true;
        }
    }
    return false;
}

inline QString GetQString(const char* dataPtr, quint32 length)
{
    QTextDecoder* decoder = QTextCodec::codecForName("UTF-16LE")->makeDecoder();
    QString qsContent = decoder->toUnicode(dataPtr, length);
    delete decoder;
    //移除终止符（如果有）
    if (qsContent.endsWith(QChar::Null)) {
        qsContent.chop(1);
    }
    return qsContent;
}
#endif // ZTTOOLS_H
