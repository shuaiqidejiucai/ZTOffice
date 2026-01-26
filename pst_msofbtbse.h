#ifndef PST_MSOFBTBSE_H
#define PST_MSOFBTBSE_H

#include "pst_base.h"

class PST_MSOfbtBSE : public PST_Base
{
public:
    PST_MSOfbtBSE(const QByteArray& srcData);

    virtual int parser()override;

    quint8 btWin32 = 0;
    quint8 btMacOS = 0;
    QByteArray rgUid;
    quint16 Tag = 0;
    quint32 Size = 0;
    quint32 cRefl = 0;
    quint32 foDelay = 0;
    quint8 Usage = 0;
    quint8 cbName = 0;
    quint8 Unused2 = 0;
    quint8 Unused3 = 0;
};

#endif // PST_MSOFBTBSE_H
