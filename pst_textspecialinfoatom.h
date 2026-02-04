#ifndef PST_TEXTSPECIALINFOATOM_H
#define PST_TEXTSPECIALINFOATOM_H

#include "pst_base.h"

class PST_TextSpecialInfoAtom : public PST_Base
{
public:
    PST_TextSpecialInfoAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_TEXTSPECIALINFOATOM_H
