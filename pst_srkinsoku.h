#ifndef PST_SRKINSOKU_H
#define PST_SRKINSOKU_H

#include "pst_base.h"

class PST_KinsokuAtom : public PST_Base
{
    PST_KinsokuAtom(const QByteArray& srcData);

};

class PST_SrKinsoku : public PST_Base
{
public:
    PST_SrKinsoku(const QByteArray& srcData);
    QList<PST_KinsokuAtom> kinsokuAtmoList;
};

#endif // PST_SRKINSOKU_H
