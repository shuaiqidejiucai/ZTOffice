#ifndef PST_SRKINSOKU_H
#define PST_SRKINSOKU_H

#include "pst_base.h"

class PST_KinsokuAtom : public PST_Base
{
public:
    PST_KinsokuAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
};

class PST_SrKinsoku : public PST_Base
{
public:
    PST_SrKinsoku(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;

    QList<QSharedPointer<PST_KinsokuAtom> > kinsokuAtmoList;
};

#endif // PST_SRKINSOKU_H
