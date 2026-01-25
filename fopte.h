#ifndef FOPTE_H
#define FOPTE_H

#include "pst_base.h"
#include "owner.h"
//TODO:获取不用PST_Base
class Fopte : public PST_Base
{
public:
    Fopte(const QByteArray& srcData);

    virtual int parser() override;

    quint16 pid : 14;
    quint8 fBid : 1;
    quint8 fComplex : 1;
    quint32 op;
};

class FOPTEComplex : public PST_Base
{
public:
    FOPTEComplex(const QByteArray& srcData);
    virtual int parser() override;
    quint16 pid : 14;
    quint8 fBid : 1;
    quint8 fComplex : 1;
    quint32 op;
    QSharedPointer<Owner> ownerPtr;
};

#endif // FOPTE_H
