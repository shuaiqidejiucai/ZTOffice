#ifndef PST_TEXTRULERATOM_H
#define PST_TEXTRULERATOM_H

#include "pst_base.h"

class PST_TextRulerAtom : public PST_Base
{
public:
    PST_TextRulerAtom(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_TEXTRULERATOM_H
