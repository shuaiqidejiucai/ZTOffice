#ifndef PST_OFFICEARTFSP_H
#define PST_OFFICEARTFSP_H

#include "pst_base.h"

class PST_OfficeArtFSP : public PST_Base
{
public:
    PST_OfficeArtFSP(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    quint32 SPID;
    quint32 fGroup;
    quint32 fChild;
    quint32 fPatriarch;
    quint32 fDeleted;
    quint32 fOleShape;
    quint32 fHaveMaster;
    quint32 fFlipH ;
    quint32 fFlipV;
    quint32 fConnector;
    quint32 fHaveAnchor;
    quint32 fBackground;
    quint32 fHaveSpt;
    quint32 unused;

};

#endif // PST_OFFICEARTFSP_H
