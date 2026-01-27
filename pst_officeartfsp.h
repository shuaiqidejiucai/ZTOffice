#ifndef PST_OFFICEARTFSP_H
#define PST_OFFICEARTFSP_H

#include "pst_base.h"

class PST_OfficeArtFSP : public PST_Base
{
public:
    PST_OfficeArtFSP(const QByteArray& srcData, const ST_Variable& var);

    quint32 SPID;
    quint32 fGroup : 1;
    quint32 fChild : 1;
    quint32 fPatriarch : 1;
    quint32 fDeleted : 1;
    quint32 fOleShape : 1;
    quint32 fHaveMaster : 1;
    quint32 fFlipH : 1;
    quint32 fFlipV : 1;
    quint32 fConnector : 1;
    quint32 fHaveAnchor : 1;
    quint32 fBackground : 1;
    quint32 fHaveSpe : 1;
    quint32 unused : 20;

};

#endif // PST_OFFICEARTFSP_H
