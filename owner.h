#ifndef OWNER_H
#define OWNER_H

#include "pst_base.h"

class Owner : public PST_Base
{
public:
    Owner(const QByteArray& srcData);

    quint16 pid : 14;
    quint8 fBid : 1;
    quint8 fComplex : 1;
    quint32 op;
};

#endif // OWNER_H
