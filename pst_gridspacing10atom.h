#ifndef PST_GRIDSPACING1_ATOM_H
#define PST_GRIDSPACING1_ATOM_H

#include "pst_base.h"

class PST_GridSpacing10Atom : public PST_Base
{
public:
    PST_GridSpacing10Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
};

#endif // PST_GRIDSPACING1_ATOM_H
