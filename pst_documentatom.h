#ifndef PST_DOCUMENTATOM_H
#define PST_DOCUMENTATOM_H
#include "global.h"
#include "pst_base.h"
class PST_DocumentAtom : public PST_Base
{
public:
    PST_DocumentAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser();
public:
    PointStruct SlideSize;
    PointStruct NotesSize;
    RatioStruct ServerZoom;

    quint32 notesMasterPersistIdRef;
    quint32 handoutsMasterPersistIdRef;
    quint16 firstSlideNumber;
    quint16 slideSizeType;
    quint8  fSaveWithFonts;
    quint8  fOmitTitlePlace;
    quint8  fRightToLeft;
    quint8  fShowComments;

};

#endif // PST_DOCUMENTATOM_H
