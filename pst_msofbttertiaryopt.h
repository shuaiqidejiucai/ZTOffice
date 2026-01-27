#ifndef PST_MSOFBTTERTIARYOPT_H
#define PST_MSOFBTTERTIARYOPT_H

#include "pst_base.h"
#include "fopte.h"

class PST_MSOfbtTertiaryOPT : public PST_Base
{
public:
    PST_MSOfbtTertiaryOPT(const QByteArray& srcData, const ST_Variable& var);

    QList<QSharedPointer<Fopte> > fopteList;
    QList<QSharedPointer<FOPTEComplex> > fopteComplexList;
};

#endif // PST_MSOFBTTERTIARYOPT_H
