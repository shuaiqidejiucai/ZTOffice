#ifndef PST_MSOFBTOPT_H
#define PST_MSOFBTOPT_H

#include "pst_base.h"

class Fopte;
class FOPTEComplex;
class PSTParser_EXPORT PST_MSOfbtOPT : public PST_Base
{
public:
    PST_MSOfbtOPT(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<Fopte> > fopteList;
    QList<QSharedPointer<FOPTEComplex> > fopteComList;
};

#endif // PST_MSOFBTOPT_H
