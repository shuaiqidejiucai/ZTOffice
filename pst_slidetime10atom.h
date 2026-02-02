#ifndef PST_SLIDETIME1_ATOM_H
#define PST_SLIDETIME1_ATOM_H

#include "pst_base.h"

class PST_SlideTime10Atom : public PST_Base
{
public:
    PST_SlideTime10Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData()override;
};

#endif // PST_SLIDETIME1_ATOM_H
