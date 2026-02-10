#ifndef PST_GRIDSPACING1_ATOM_H
#define PST_GRIDSPACING1_ATOM_H

#include "pst_base.h"

class PSTParser_EXPORT PST_GridSpacing10Atom : public PST_Base
{
public:
    PST_GridSpacing10Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_GRIDSPACING1_ATOM_H
