#ifndef PST_MSOFBTOPT_H
#define PST_MSOFBTOPT_H

#include "pst_base.h"
#include "fopte.h"
class PST_MSOfbtOPT : public PST_Base
{
public:
    PST_MSOfbtOPT(const QByteArray& srcData);

    virtual int parser()override;

    QList<QSharedPointer<Fopte> > fopteList;
    QList<QSharedPointer<FOPTEComplex> > fopteComList;
};

#endif // PST_MSOFBTOPT_H
