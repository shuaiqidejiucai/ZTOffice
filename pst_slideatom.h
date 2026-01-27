#ifndef PST_SLIDEATOM_H
#define PST_SLIDEATOM_H

#include "pst_base.h"

class PST_SlideAtom : public PST_Base
{
public:
    PST_SlideAtom(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_SLIDEATOM_H
