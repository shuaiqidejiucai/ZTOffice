#ifndef PST_COLORSCHEMEATOM_H
#define PST_COLORSCHEMEATOM_H

#include "pst_base.h"

class PST_ColorSchemeAtom : public PST_Base
{
public:
    PST_ColorSchemeAtom(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_COLORSCHEMEATOM_H
