#ifndef PST_TEXTCHARSATOM_H
#define PST_TEXTCHARSATOM_H

#include "pst_base.h"

class PST_TextCharsAtom : public PST_Base
{
public:
    PST_TextCharsAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_TEXTCHARSATOM_H
