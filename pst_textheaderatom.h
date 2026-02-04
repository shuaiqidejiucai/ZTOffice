#ifndef PST_TEXTHEADERATOM_H
#define PST_TEXTHEADERATOM_H

#include "pst_base.h"

class PST_TextHeaderAtom : public PST_Base
{
public:
    PST_TextHeaderAtom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    quint32 textType;
};

#endif // PST_TEXTHEADERATOM_H
