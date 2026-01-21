#ifndef PST_MSOFBTBSE_H
#define PST_MSOFBTBSE_H

#include "pst_base.h"

class PST_MSOfbtBSE : public PST_Base
{
public:
    PST_MSOfbtBSE(const QByteArray& srcData);

    quint8 btWin32;
    quint8 btMacOS;
    QByteArray rgUid;
    quint16 Tag;
    quint32 Size;
    quint32 cRefl;
    quint32 foDelay;
    quint8 Usage;
    quint8 cbName;
    quint8 Unused2;
    quint8 Unused3;
};

#endif // PST_MSOFBTBSE_H
