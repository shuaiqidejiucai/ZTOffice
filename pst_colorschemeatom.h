#ifndef PST_COLORSCHEMEATOM_H
#define PST_COLORSCHEMEATOM_H

#include "pst_base.h"

class PST_ColorSchemeAtom : public PST_Base
{
public:
    PST_ColorSchemeAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_COLORSCHEMEATOM_H
