#ifndef PST_MSOFBTTERTIARYOPT_H
#define PST_MSOFBTTERTIARYOPT_H

#include "pst_base.h"

class Fopte;
class FOPTEComplex;
class PST_MSOfbtTertiaryOPT : public PST_Base
{
public:
    PST_MSOfbtTertiaryOPT(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<Fopte> > fopteList;
    QList<QSharedPointer<FOPTEComplex> > fopteComplexList;
};

#endif // PST_MSOFBTTERTIARYOPT_H
